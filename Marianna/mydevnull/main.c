#include <linux/module.h> 
#include <linux/fs.h>
#include <linux/device.h> 
#include <linux/slab.h>
#include <linux/cdev.h> 
#include <linux/printk.h> /*for pr_err*/

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marianna");
MODULE_DESCRIPTION("implementation for /dev/null");

/* how many minors do we need ? */
const int MINOR_COUNT = 1;


static int myNull_open(struct inode *inode, struct file *file)
{	
	pr_info("we are here in open function!!!\n");
	return 0;
}

static ssize_t myNull_write( struct file *file, const char __user *buf , size_t count, loff_t *ppos)
{
	pr_info("we are here in read function!!!\n");
	return count;
}

static int myNull_release(struct inode *inode, struct file *file)
{
	pr_info("we are here in release function!!!\n");
	return 0;
}

static const struct file_operations myNull_fops = {
	.owner = THIS_MODULE,
	.open = myNull_open,
	.write = myNull_write,
	.release = myNull_release,
};
/* this is the first dev_t allocated to us... */
static dev_t first_dev;
/* this variable will store the class */
static struct class *my_class;
/* this variable will hold our cdev struct */
static struct cdev my_cdev;
static struct device* my_device;
/* this is the operations table */



static int __init myNull_init(void)
{
	int err = 0;
	/* allocate our own range of devices */
	err = alloc_chrdev_region(&first_dev, 0, MINOR_COUNT, THIS_MODULE->name);
	if (err) {
		pr_err("cannot alloc_chrdev_region\n");
		goto err_final;
	}
	pr_info("allocated the region\n");
	
	/* add the cdev structure, no error codes */
	cdev_init(&my_cdev, &myNull_fops);
	err = cdev_add(&my_cdev, first_dev, MINOR_COUNT);
	if (err) {
		pr_err("cannot cdev_add\n");
		goto err_dealloc;
	}
	pr_info("added the cdev\n");

	my_class = class_create(THIS_MODULE, THIS_MODULE->name);
	if (IS_ERR(my_class)) {
		pr_err("failed in class_create\n");
		err = PTR_ERR(my_class);
		goto err_dealloc;
	}
	pr_info("created the class\n");
	
	/* and now lets auto-create a /dev/null*/
	my_device = device_create(my_class, NULL, first_dev, NULL, "%s", THIS_MODULE->name);
	if (IS_ERR(my_device)) {
		pr_err("failed in device_create\n");
		err = PTR_ERR(my_device);
		goto err_class;
	}
	pr_info("created the device\n");
	
	pr_info("loaded ok\n");

	return 0;


err_class:
	class_destroy(my_class); /*destroys a struct class structure*/
err_dealloc:
	unregister_chrdev_region(first_dev, MINOR_COUNT);
err_final:
	return err;	
}

static void __exit myNull_exit(void)
{
	device_destroy(my_class, first_dev);
	class_destroy(my_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(first_dev, MINOR_COUNT);
	pr_info("unloaded ok\n");
}

module_init(myNull_init);
module_exit(myNull_exit);
