/* #define DEBUG */
#include <linux/module.h> /* for MODULE_*, module_* */
#include <linux/list.h>   /* for linked list */
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>
#include "mq.h"

#define DO_MUTEX
#define DO_WAIT_RECV

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alona Korzhnev");
MODULE_DESCRIPTION("message queue /dev/mq*");

static int mq_count = 8;
static dev_t first_dev;
static struct class* my_class;
static struct cdev cdev;
static int first_minor = 0;
static struct mq_t* m_queues;

struct list_element_t
{
	struct list_head node;
	char* data;
	int size;
};

struct mq_t
{
	struct list_head head;
	struct device* device;
	struct mutex lock;
	wait_queue_head_t read_wait_queue;
	wait_queue_head_t write_wait_queue;
	int size;
	int capacity;
};

static inline void message_queue_ctor(struct mq_t* mq)
{
	INIT_LIST_HEAD(&mq->head);
	mutex_init(&mq->lock);
	init_waitqueue_head(&mq->read_wait_queue);
	init_waitqueue_head(&mq->write_wait_queue);
	mq->device = NULL;
	mq->size = 0;
	mq->capacity = 100;
}

static inline void mq_dtor(struct mq_t* mq)
{
     struct list_element_t* message;
     list_for_each_entry(message, &mq->head, node)
     {
         kfree(message->data);
         kfree(message);
     }
     mutex_destroy(&mq->lock);
}

static int mq_open(struct inode* inode, struct file* fp)
{
	int mq_number = iminor(inode) - MINOR(first_dev);
	struct mq_t *mq = m_queues + mq_number;
	fp->private_data = mq;
	return 0;
}

static int my_list_not_empty(struct mq_t* mq)
{
	int ret;
	mutex_lock(&mq->lock);
	ret = !list_empty(&mq->head); 
	if(!ret)
		mutex_unlock(&mq->lock);
	return ret;
}

static int my_list_has_space(struct mq_t* mq)
{
	int ret;
	mutex_lock(&mq->lock);
	ret = mq->size < mq->capacity; 
	if(!ret)
		mutex_unlock(&mq->lock);
	return ret;
}

static long mq_ioctl(struct file* fp, unsigned int op, unsigned long arg)
{
	struct mq_t *mq = fp->private_data;
	int ret;
	char* buffer;
	struct mq_reg reg;
	struct mq_reg* argp = (struct mq_reg*)arg;
	struct list_element_t* new_message;
	int size_to_return;

	switch (op)
	{
	case MQ_SEND_MSG:
		ret = copy_from_user(&reg, argp, sizeof(reg));
		if(ret)
		{
			pr_err("%s: error copy\n", THIS_MODULE->name);
			return ret;
		}
		buffer = kmalloc(reg.size, GFP_KERNEL);
		if(IS_ERR(buffer))
		{
			pr_err("%s: error kmalloc", THIS_MODULE->name);
			return PTR_ERR(buffer);
		}
		ret = copy_from_user(buffer, reg.data, reg.size);
		if(ret)
		{
			pr_err("%s:error copy\n", THIS_MODULE->name);
			return ret;
		}
		new_message = kmalloc(sizeof(struct list_element_t), GFP_KERNEL);
		if(IS_ERR(new_message))
		{
			pr_err("%s: error kmalloc", THIS_MODULE->name);
			ret = PTR_ERR(new_message);
			return ret;
		}

		new_message->data = buffer;
		new_message->size = reg.size;
		size_to_return = reg.size;

	 	ret = wait_event_interruptible(mq->write_wait_queue, my_list_has_space(mq));
		if(ret == -ERESTARTSYS)
		{
			/* someone is trying to kill me! */
			/* no need to free the mutex here */
			return ret;
		}
		list_add_tail(&new_message->node, &mq->head);
		mq->size++;
		mutex_unlock(&mq->lock);
		wake_up_all(&mq->read_wait_queue);
		return size_to_return;

	case MQ_RECV_MSG:
	 	ret = wait_event_interruptible(mq->read_wait_queue, my_list_not_empty(mq));
		if(ret == -ERESTARTSYS)
		{
			/* someone is trying to kill me! */
			/* no need to free the mutex here */
			return ret;
		}
		new_message = list_entry((&mq->head)->prev, struct list_element_t, node);
		list_del((&mq->head)->prev);
		mq->size--;
		mutex_unlock(&mq->lock);
		wake_up_all(&mq->write_wait_queue);
		size_to_return=new_message->size;
		ret = copy_to_user((char*)arg, new_message->data, new_message->size);
		if(ret)
		{
			pr_err("%s: error copy\n", THIS_MODULE->name);
			return ret;
		}
		kfree(new_message->data);
		kfree(new_message);
		return size_to_return;

	default:
		return -ENOTTY;
	}
	return -ENOTTY;
}

/* all device operetions */
static const struct file_operations mq_fops =
{
	.owner = THIS_MODULE,
	.open = mq_open,
	.unlocked_ioctl = mq_ioctl,
};

/* initialize queue message */
static int __init message_queue_init(void)
{
	int ret;
	int i;
	pr_info("%s: allocating queues\n", THIS_MODULE->name);
	m_queues = kmalloc(sizeof(struct mq_t)*mq_count, GFP_KERNEL);
	if(IS_ERR(m_queues))
	{
		pr_err("%s: kmalloc\n", THIS_MODULE->name);
		ret = PTR_ERR(m_queues);
		goto err_return;
	}
	for(i = 0; i < mq_count; i++)
		message_queue_ctor(m_queues + i);
	pr_info("%s: done allocating queues\n", THIS_MODULE->name);

	pr_info("%s: allocating majors/minors\n", THIS_MODULE->name);
	ret = alloc_chrdev_region(&first_dev, first_minor, mq_count,
							  THIS_MODULE->name);
	if(ret)
	{
		pr_err("%s: cannot alloc_chrdev_region\n", THIS_MODULE->name);
		goto err_final;
	}
	pr_info("%s: done allocating majors/minors\n", THIS_MODULE->name);

	pr_info("%s: add cdev\n", THIS_MODULE->name);
	cdev_init(&cdev, &mq_fops);
	ret = cdev_add(&cdev, first_dev, mq_count);
	if(ret)
	{
		pr_err("%s: cannot cdev_add\n", THIS_MODULE->name);
		goto err_dealloc;
	}
	pr_info("%s: done add cdev\n", THIS_MODULE->name);

	pr_info("%s: create class\n", THIS_MODULE->name);
	my_class = class_create(THIS_MODULE, THIS_MODULE->name);
	if(IS_ERR(my_class))
	{
		pr_err("%s: class_create\n", THIS_MODULE->name);
		ret = PTR_ERR(my_class);
		goto err_cdev_del;
	}
	pr_info("%s: done create class\n", THIS_MODULE->name);

	pr_info("%s: device_create\n", THIS_MODULE->name);
	for(i = 0; i < mq_count; i++)
	{
		m_queues[i].device = device_create(my_class, NULL,
									  MKDEV(MAJOR(first_dev), MINOR(first_dev) + i),
									  NULL, "%s%d", THIS_MODULE->name, i);
		if(IS_ERR(m_queues[i].device))
		{
			pr_err("device_create\n");
			ret = PTR_ERR(m_queues[i].device);
			goto err_class;
		}
	}
	pr_info("%s: done device_create\n", THIS_MODULE->name);
	pr_info("%s: loaded successfully\n", THIS_MODULE->name);
	return 0;
	/*
err_device:
	for(i = 0; i < mq_count; i++) 
	{
		device_destroy(my_class, MKDEV(MAJOR(first_dev),
			MINOR(first_dev)+i));
	}
	*/
err_class:
	class_destroy(my_class);
err_cdev_del:
	cdev_del(&cdev);
err_dealloc:
	unregister_chrdev_region(first_dev, mq_count);
err_final:
	for(i = 0; i < mq_count; i++)
		mq_dtor(m_queues + i);
	kfree(m_queues);
err_return:
	return ret;
}

static void __exit message_queue_exit(void)
{
	int i;
	for(i = 0; i < mq_count; i++)
		device_destroy(my_class, MKDEV(MAJOR(first_dev), MINOR(first_dev) + i));
	class_destroy(my_class);
	cdev_del(&cdev);
	unregister_chrdev_region(first_dev, mq_count);
	for (i = 0; i < mq_count; i++)
		mq_dtor(m_queues + i);
	kfree(m_queues);
	pr_info("%s: unloaded successfully\n", THIS_MODULE->name);
}

module_init(message_queue_init);
module_exit(message_queue_exit);
