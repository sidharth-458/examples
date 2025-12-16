#define pr_fmt(fmt) KBUILD_MODNAME ": %s: " fmt "\n" , __func__
#include<linux/module.h>
#include<linux/kthread.h>
#include<linux/completion.h>
#include<linux/delay.h>
DECLARE_COMPLETION(sleep_done);

static int delay(void *){
	msleep(10000);
	complete(&sleep_done);
	return 0;
}


static int __init comp_init(void){
	pr_info("setup");
	kthread_run(delay,NULL,"delay0");
	return 0;
}

static void __exit comp_exit(void){
	wait_for_completion(&sleep_done);
}



module_init(comp_init);
module_exit(comp_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SIDHARTH SEELA");
