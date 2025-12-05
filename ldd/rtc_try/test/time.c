#define pr_fmt(fmt) KBUILD_MODNAME": "fmt"\n"
#include<linux/module.h>
#include<linux/init.h>
#include<linux/device.h>
#include<linux/timer.h>
#include<linux/ioctl.h>
#include<linux/cdev.h>
#include<linux/mutex.h>
#include<asm/uaccess.h>
#include"if.h"
static dev_t tim_dev;
static struct cdev tim_cdev;
static struct class * tim_class;
static struct device* tim_device;
static struct timer_list tim_timer;
static DEFINE_MUTEX(tim_mutex);
static int tim_starttime = 0;
module_param(tim_starttime,int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(tim_starttime, "startime for module");

static unsigned long startjiffy;
static int count;
static int tim_currtime;
static bool lock = false;

static ssize_t tim_read(struct file * fp,char __user * buff, size_t len, loff_t *ppos){
	int ret = 0;
	if(mutex_trylock(&tim_mutex) && *ppos == 0){
		char lbuff[30] = {0};
		snprintf(lbuff,30,"%d\n",tim_currtime);
		int llen = strlen(lbuff);
		if(!copy_to_user(buff,lbuff,llen)){
			mutex_unlock(&tim_mutex);
			return -EFAULT;
		}
		mutex_unlock(&tim_mutex);
		ret = llen;
	}
	return ret;
}

static ssize_t tim_write(struct file * fp,const char __user * buff, size_t len, loff_t *ppos){
	int ret = 0;
	if(mutex_trylock(&tim_mutex) && *ppos == 0){
		int res;
		if(kstrtoint_from_user(buff,len,10,&res)){
			return -EFAULT;
		}
		tim_currtime = res;
		mutex_unlock(&tim_mutex);
		ret = len;
	}
	return ret;
}
static long tim_ioctl(struct file * fp, unsigned int cmd, unsigned long arg){
	switch(cmd){
		case LOCK_CMD:
			lock = true;
			break;
		case UNLOCK_CMD:
			lock = false;
			break;
		default:
			return -1;
	}
	return 0;
}
static struct file_operations tim_fops = {
	.owner = THIS_MODULE,
	.read = tim_read,
	.write = tim_write,
	.unlocked_ioctl = tim_ioctl,
};
static void tim_callback(struct timer_list * timer){
	mod_timer(timer, startjiffy + count * msecs_to_jiffies(1000));
	count++;
	if(!lock)
		tim_currtime++;
}
static int __init tim_init(void){
	alloc_chrdev_region(&tim_dev, 0, 1,KBUILD_MODNAME);

	cdev_init(&tim_cdev,&tim_fops);

	cdev_add(&tim_cdev,tim_dev,1);

	tim_class = class_create(KBUILD_MODNAME);

	tim_device = device_create(tim_class,NULL,tim_dev, NULL,KBUILD_MODNAME"0");
	
	timer_setup(&tim_timer,&tim_callback,0);
	
	startjiffy = jiffies;
	count = 1;
	tim_currtime = tim_starttime;
	mod_timer(&tim_timer, startjiffy + count * msecs_to_jiffies(1000));
	count++;

	return 0;
}
static void __exit tim_exit(void){
	timer_shutdown(&tim_timer);
	timer_delete(&tim_timer);
	device_destroy(tim_class,tim_dev);
	class_destroy(tim_class);
	cdev_del(&tim_cdev);
	unregister_chrdev_region(tim_dev,1);
}

module_init(tim_init);
module_exit(tim_exit);
MODULE_AUTHOR("Sidharth Seela <sidharthseela@gmail.com>");
MODULE_LICENSE("GPL");
