#include "mq.h"

#include <linux/module.h> /* for MODULE_*, module_* */
#include <linux/moduleparam.h> /* for module_param, MODULE_PARM_DESC */
#include <linux/fs.h> /* for fops */
#include <linux/device.h> /* for class_create */
#include <linux/slab.h> /* for kzalloc */
#include <linux/uaccess.h> /* for copy_to_user, access_ok */
#include <linux/cdev.h> /* for cdev_* */
#include <linux/wait.h> /* for wait_queue_head_t and ops on it */

#define MESSAGE_SIZE 4096

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alona Korzhnev");
MODULE_DESCRIPTION("implementation for /dev/mq");

static int mq_count = 8;
static dev_t first_dev;

struct message_t
{
    struct list_head node;
    char* data;
    int size;
};

struct mq_t
{
    int size;
    struct list_head head;
    struct device *mq_device;
    wait_queue_head_t wait_queue;
    /* capacity */
};

static struct mq_t *m_queues;
static int first_minor;

/* this variable will hold our cdev struct */
static struct cdev cdev;
/* this variable will store the class */
static struct class *my_class;


static int mq_open(struct inode* inode, struct file* file)
{
    int mq_number = iminor(inode) - MINOR(first_dev);
	struct mq_t* mq = m_queues + mq_number;
    file->private_data = mq;
    return 0;
}

static int mq_release(struct inode* inode, struct file* file)
{
    /*to do*/
    return 0;
}

static void message_dtor(struct message_t* m)
{
    kfree(m->data);
    kfree(m);
}

static long mq_ioctl(struct file* file, unsigned int op, unsigned long arg)
{
    struct mq_t* mq = file->private_data;
    int ret, res = 0;
    struct mq_reg r;
    struct mq_reg* argp = (struct mq_reg*)arg;

    char* buff;
    struct message_t* entry;

    pr_info("in ioctl with option %u\n", op);

    switch(op)
    {
        /* set message */
        case MQ_SEND_MSG:
            ret = copy_from_user(&r, argp, sizeof(r));
            if(ret < 0)
            {
                pr_err("%s: error in copy_from_user\n", THIS_MODULE->name);
                /* go to */
            }
            pr_info("copy from user struct\n");

            buff = (char*)kmalloc(r.size, GFP_KERNEL);
            if(IS_ERR(buff))
            {
                pr_err("%s: error in kmalloc\n", THIS_MODULE->name);
                /* go to */
            }

            ret = copy_from_user(buff, r.data, r.size);
            if(ret < 0)
            {
                pr_err("%s: error in copy_from_user\n", THIS_MODULE->name);
                /* go to */
            }
            pr_info("copy from user data\n");

            entry = (struct message_t*)kmalloc(sizeof(struct message_t), GFP_KERNEL);
            if(IS_ERR(buff))
            {
                pr_info("%s: error in kmalloc\n", THIS_MODULE->name);
                /* go to */
            }
            pr_info("kmalloc struct new_message\n");

            entry->data = buff;
            entry->size = r.size;
            pr_info("set data in struct new_message\n");

            list_add(&entry->node, &mq->head);
            pr_info("list_add new_message\n");

            wake_up_interruptible(&mq->wait_queue);
            res = entry->size;
            pr_info("in end send\n");
            break;

        /* get message */
        case MQ_RECV_MSG:
            ret = wait_event_interruptible(mq->wait_queue, list_empty(&mq->head) == 0);
            if(ret)
            {
                pr_err("%s: error in wait_event_interruptible\n", THIS_MODULE->name);
            }
            pr_info("in begin recive\n");
            entry = list_entry((&mq->head)->prev, struct message_t, node);
            res = entry->size;
            pr_info("entry->size %d\n", entry->size);
            ret = copy_to_user((char*)arg, entry->data, entry->size);
            if(ret < 0)
            {
                pr_err("%s: error in copy_to_user\n", THIS_MODULE->name);
                
            }
            list_del((&mq->head)->prev);
            message_dtor(entry);
            pr_info("list delete element\n");
            break;        
        
        default:
            break;
    }
    return res;
}

/* this is the operations table */
static const struct file_operations mq_fops = 
{
	.owner = THIS_MODULE,
    .open = mq_open,
    .release = mq_release,
    .unlocked_ioctl = mq_ioctl,
};

static void mq_ctor(struct mq_t* mq)
{
    mq->size = 0;
    INIT_LIST_HEAD(&(mq->head));
	mq->mq_device = NULL;
    init_waitqueue_head(&mq->wait_queue);
}

static void mq_dtor(struct mq_t* mq)
{
    struct message_t* entry;
    struct list_head* ptr;

    pr_info("in enter function mq_dtor\n");

    for(ptr = mq->head.next; ptr != &mq->head; ptr = ptr->next)
    {
        entry = list_entry(ptr, struct message_t, node);
        list_del(&entry->node);
        kfree(entry->data);
        kfree(entry);
    }

    pr_info("in exit function mq_dtor\n");
}

static int __init mq_init(void)
{
    int ret;
    int i;

    /* allocate all m_queues */
	m_queues = kmalloc(sizeof(struct mq_t)*mq_count, GFP_KERNEL);
    if(IS_ERR(m_queues))
    {
        pr_err("kmalloc\n");
        ret = PTR_ERR(m_queues);
    }

    /* initialize all m_queues */
    for(i = 0; i < mq_count; ++i)
        mq_ctor(m_queues + i);

    /* allocate our own range of devices */
    ret = alloc_chrdev_region(&first_dev, first_minor, mq_count, THIS_MODULE->name);
    if(ret)
    {
        pr_err("cannot alloc_chrdev_region\n");
    }
    pr_info("allocated the region\n");

    /* add the cdev structure */
    cdev_init(&cdev, &mq_fops);
    ret = cdev_add(&cdev, first_dev, mq_count);
    if(ret)
    {
        pr_err("cannot cdev_add\n");
    }
    pr_info("added the cdev\n");

    /* this is creating a new class (/proc/devices) */
    my_class = class_create(THIS_MODULE, THIS_MODULE->name);
    if(IS_ERR(my_class))
    {
        pr_err("class_create\n");
        ret = PTR_ERR(my_class);
    }
    pr_info("created the class\n");

    for(i = 0; i < mq_count; ++i)
    {
        /* and now lets auto-create a /dev/ node */
        m_queues[i].mq_device = device_create(my_class, NULL,
                    MKDEV(MAJOR(first_dev), MINOR(first_dev) + i),
                    NULL, "%s%d", THIS_MODULE->name, i);
        if(IS_ERR(m_queues[i].mq_device))
        {
            pr_err("device_create\n");
            ret = PTR_ERR(m_queues[i].mq_device);
        }
    }

    pr_info("loaded successfully\n");
    return 0;
}

static void __exit mq_exit(void)
{
	int i;
    for(i = 0; i < mq_count; ++i)
        device_destroy(my_class, MKDEV(MAJOR(first_dev),
                MINOR(first_dev) + i));
    class_destroy(my_class);
    cdev_del(&cdev);
    unregister_chrdev_region(first_dev, mq_count);
    for(i = 0; i < mq_count; ++i)
        mq_dtor(m_queues + i);
    kfree(m_queues);
    pr_info("unloaded successfully\n");
}

module_init(mq_init);
module_exit(mq_exit);