#define pr_fmt(fmt) KBUILD_MODNAME": %s:"fmt"\n" , __func__
#include<linux/init.h>		/* for __init,__exit,THIS_MODULE*/
#include<linux/module.h>	/* for module_init(), module_exit()*/
#include<linux/cdev.h>		/* for cdev_add() ,cdev_init(), struct cdev*/
#include<linux/fs.h>		/* for alloc_chrdev_region()*/
#include<linux/device.h>	/* for dev_t, device_create()*/
#include<linux/device/class.h>	/* for class_create()*/
#include<linux/err.h>
#include"fops.c"
#include<linux/miscdevice.h>
static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = KBUILD_MODNAME"-new",
	.fops = &fops,
};
static int __init charu_init(void){
	misc_register(&misc);
	pr_info("registered");
	return 0;


}

static void __exit charu_exit(void){
	misc_deregister(&misc);
	pr_info("unregistered");
}


MODULE_AUTHOR("Sidharth Seela<sidharthseela@gmail.com");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple characted device");
MODULE_SOFTDEP("pre: psmouse"); 
module_init(charu_init);
module_exit(charu_exit);
