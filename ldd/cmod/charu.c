#define pr_fmt(fmt) KBUILD_MODNAME": "fmt"\n"
#include<linux/init.h>		/* for __init,__exit,THIS_MODULE*/
#include<linux/module.h>	/* for module_init(), module_exit()*/
#include<linux/cdev.h>		/* for cdev_add() ,cdev_init(), struct cdev*/
#include<linux/fs.h>		/* for alloc_chrdev_region()*/
#include<linux/device.h>	/* for dev_t, device_create()*/
#include<linux/device/class.h>	/* for class_create()*/
#include<linux/err.h>
static struct cdev c_dev;
static struct file_operations fops = {
				.owner = THIS_MODULE
				};
static struct class * sys;
static struct device * dev;
static dev_t device_id;
static int __init charu_init(void){
	int err;
	
	err = alloc_chrdev_region(&device_id,0,1,KBUILD_MODNAME);
	if(err){
		pr_err("alloc_chardev_region failed %d",err);
		goto chrdev;
	}
	else{
		pr_info("alloc_chardev_region gave device_id %d(%d:%d)",device_id, MAJOR(device_id),MINOR(device_id));
	}
	
	cdev_init(&c_dev,&fops);
	pr_info("cdev_init initialzed cdev and attached fops to it");

	err = cdev_add(&c_dev, device_id,1);
	if(err){
		pr_err("cdev_add failed %d",err);
		goto cdev;
	}
	else{
		pr_info("cdev_add success, cdev registered in kernel to device_id %d",device_id);
	}
	
	sys = class_create(KBUILD_MODNAME);
	if(IS_ERR(sys)){
		err = PTR_ERR(sys);
		pr_err("class_create failed %d",err);
		goto class;
	}
	else{
		pr_info("class_create success, sysfs must have " KBUILD_MODNAME);
	}

	dev = device_create(sys,NULL,device_id,NULL,KBUILD_MODNAME"0");
	if(IS_ERR(dev)){
		err = PTR_ERR(dev);
		pr_err("device_create failed %d",err);
		goto dev;
	}
	else{
		pr_info("device_create success, devfs must have " KBUILD_MODNAME"0");
	}

	return 0;

dev:
	class_destroy(sys);
class:
	cdev_del(&c_dev);
cdev:
	unregister_chrdev_region(device_id,1);
chrdev:
	return err;


}

static void __exit charu_exit(void){
	pr_info("device destroyed from /dev");
	device_destroy(sys,device_id);

	pr_info("class destroyed from /sys");
	class_destroy(sys);

	pr_info("cdev object free'd from kernel");
	cdev_del(&c_dev);

	pr_info("chrdev region free'd");
	unregister_chrdev_region(device_id,1);
}


MODULE_AUTHOR("Sidharth Seela<sidharthseela@gmail.com");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple characted device");
MODULE_SOFTDEP("pre: psmouse"); 
module_init(charu_init);
module_exit(charu_exit);
