#define pr_fmt(fmt) KBUILD_MODNAME": "fmt"\n"
#include<linux/module.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#include<linux/string.h>
static ssize_t procread(struct file * filp, char __user * user, size_t len, loff_t * off){
	char * str = "hello\n";
	if(*off > strlen(str))
		return -ENOMEM;
	if(len > strlen(str) - *off)
		len = strlen(str) - *off;
	str = str + *off;
	copy_to_user(user,str,len);
	*off = len;
	return len;
}

static ssize_t procwrite(struct file * filp, const char __user * user, size_t len, loff_t * off){
	return 0;
}

static struct proc_ops proc = {
	.proc_read = procread,
	.proc_write = procwrite,
};

static int __init init(void){
	pr_info("loaded");
	proc_create("MY_PROC",0666,NULL,&proc);
	return 0;
}
static void __exit exit(void){
	pr_info("removed");
	remove_proc_entry("MY_PROC",NULL);
}

module_init(init);
module_exit(exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sidharth Seela <sidharthseela@gmail.com");
//MODULE_DESC("To create an entry in procfs");
