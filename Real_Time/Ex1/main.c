#include <linux/module.h>
#include <linux/printk.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alona Korzhnev");
MODULE_DESCRIPTION("A module showing off module parameters");
MODULE_VERSION("1.0.0");

static int param = 1;
module_param(param, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
MODULE_PARM_DESC(param, "myint controls bla bla bla...");


static int __init param_exe_init(void)
{
	pr_info("in param_exe_init\n");
	pr_info("in param_exe_init: param is %d\n", param);
	return 0;
}

static void __exit param_exe_exit(void)
{
	pr_info("in param_exe_exit: param is %d\n", param);
	pr_info("in param_exe_exit\n");
}

module_init(param_exe_init);
module_exit(param_exe_exit);