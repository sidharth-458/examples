#include <linux/module.h>    // Require	d for kernel modules
#include <linux/kernel.h>    // Required for printk()
#include <linux/fs.h>        // Required for file_operations
#include <asm/uaccess.h>     // Required for copy_to_user/copy_from_user
#include<linux/ioctl.h>
#include"time_if.h"

/*
 * @brief the time counter variable
 */
static int starttime = 0;
module_param(starttime,int,S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(starttime,"unix starttime");

/*
 * @brief ioctl lock parameter, helps to stop incrementing
 */
static bool lock = false;

/* 
 * @brief callback to just show open
 */
static int device_open(struct inode *inode, struct file *file) {
	pr_info("device_open()");
	return 0;
}

/*
 * @brief callback to just show close
 */
static int device_release(struct inode *inode, struct file *file) {
	pr_info("device_release()");
	return 0;
}

/*
 * @brief read function makes use of mutex for sequential reads
 */
static ssize_t device_read(struct file *file, char __user * buffer, size_t len, loff_t *offset) {
	ssize_t ret = 0;
	if(*offset == 0 && mutex_trylock(&mutex) ){
		char buff[30] = {0};
		ssize_t bufflen = snprintf(buff,30,"%d\n",starttime);
		if (copy_to_user(buffer, buff, bufflen) != 0) {
        		return -EFAULT; // Bad address
    		}
		mutex_unlock(&mutex);
		pr_info("%zd read",bufflen);
		*offset = bufflen;
		ret = bufflen;
	}
	return ret;
}

/*
 * @brief write function uses direct copy to int function, and uses it to overwrite startime
 */
static ssize_t device_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset) {
	if(lock)
		return -EPERM;
	if(len > 30)
		return -ENOSPC;
	int res;
	if(kstrtoint_from_user(buffer, len,10,&res)){
		return -EFAULT;
	}
	starttime = res;
    	pr_info("%zd written",len);
	return len;
}

/*
 * @brief ioctl is implemented for locks and unlock of incrementing time
 */
static long device_ioctl(struct file * file, unsigned int cmd, unsigned long arg){
	pr_info("ioctl called %d",cmd);
	switch(cmd){
		case TIME_LOCK:
			lock = true;
			break;
		case TIME_UNLOCK:
			lock = false;
			break;
		default:
			return -EINVAL;
			break;
	}
	return 0;
}
/*
 * @brief this is used inside timer callback to add time only if unlocked
 */
static void add_time(void){
	if(!lock)
		starttime++;
	pr_info("time is %d",starttime);
}

/*
 * @brief struct to assign to cdev_init
 */
static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
    .unlocked_ioctl = device_ioctl,
    .owner = THIS_MODULE
};

