#define pr_fmt(fmt) KBUILD_MODNAME": "fmt"\n"
#include<linux/init.h>		/* for __init,__exit,THIS_MODULE*/
#include<linux/module.h>	/* for module_init(), module_exit()*/
#include<linux/cdev.h>		/* for cdev_add() ,cdev_init(), struct cdev*/
#include<linux/fs.h>		/* for alloc_chrdev_region()*/
#include<linux/device.h>	/* for dev_t, device_create()*/
#include<linux/device/class.h>	/* for class_create()*/
#include<linux/err.h>
#include<linux/timer.h>		/* for mod_timer() timer_setup() */

static DEFINE_MUTEX(mutex);
#include"fops.c"
static struct cdev c_dev;
static struct class * sys;
static struct device * dev;
static dev_t device_id;
static struct timer_list timer;
static unsigned long startjiffy;
static int count = 1;

/* 
 * @brief timer callback which rearms the timer to the next multiple added to starttime.
 */
static void timer_callback(struct timer_list * tim){
	mod_timer(tim, startjiffy + count * msecs_to_jiffies(1000));
	add_time();
	count++;
}
/*
 * @brief the init function
 */
static int __init tim_init(void){
	int err;
/*
 * @brief alloc deviceid
 */
	err = alloc_chrdev_region(&device_id,0,1,KBUILD_MODNAME);
	if(err){
		pr_err("alloc_chardev_region failed %d",err);
		goto chrdev;
	}
	else{
		pr_info("alloc_chardev_region gave device_id %d(%d:%d)",device_id, MAJOR(device_id),MINOR(device_id));
	}
/*
 * @brief initialize cdev struct
 */
	cdev_init(&c_dev,&fops);
	pr_info("cdev_init initialzed cdev and attached fops to it");
/*
 * @brief register cdev to the kernel
 */
	err = cdev_add(&c_dev, device_id,1);
	if(err){
		pr_err("cdev_add failed %d",err);
		goto cdev;
	}
	else{
		pr_info("cdev_add success, cdev registered in kernel to device_id %d",device_id);
	}

/*
 * @brief create class object and poplutate sysfs
 */
	sys = class_create(KBUILD_MODNAME);
	if(IS_ERR(sys)){
		err = PTR_ERR(sys);
		pr_err("class_create failed %d",err);
		goto class;
	}
	else{
		pr_info("class_create success, sysfs must have " KBUILD_MODNAME);
	}
/*
 * @brief create deviceobject and populate devfs
 */
	dev = device_create(sys,NULL,device_id,NULL,KBUILD_MODNAME"0");
	if(IS_ERR(dev)){
		err = PTR_ERR(dev);
		pr_err("device_create failed %d",err);
		goto dev;
	}
	else{
		pr_info("device_create success, devfs must have " KBUILD_MODNAME"0");
	}

/*
 * @brief create timer and attach callback
 */
	timer_setup(&timer,timer_callback,0);

/*
 * @brief rearm and attach callbacks
 */
	startjiffy = jiffies;
	mod_timer(&timer,startjiffy + count * msecs_to_jiffies(1000));
	count++;
	pr_info("timer created\n");

	return 0;
/*
 * @brief cleanup path if improper init
 */
dev:
	class_destroy(sys);
class:
	cdev_del(&c_dev);
cdev:
	unregister_chrdev_region(device_id,1);
chrdev:
	return err;


}

static void __exit tim_exit(void){
	pr_info("timer deleted");
	timer_shutdown(&timer);
	timer_delete(&timer);

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
MODULE_DESCRIPTION("A simple timing device");
module_init(tim_init);
module_exit(tim_exit);
