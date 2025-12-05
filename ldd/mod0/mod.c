#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt "\n"
#include<linux/init.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/kthread.h>
#include<linux/delay.h>
static struct task_struct * mod_thread_struct;
static int mod_thread(void * d){
	while(!kthread_should_stop()){
		pr_info("thread running");
		ssleep(3);
	}
	return 0;
}
__init static int mod_init(void){
	mod_thread_struct = kthread_run(mod_thread,NULL,"[" KBUILD_MODNAME "]");
	if(IS_ERR(mod_thread_struct)){
		pr_warn("thread create failed");
		return -(int)PTR_ERR((void *)mod_thread_struct);
	}
	return 0;
}

__exit static void mod_exit(void){
	int ret = kthread_stop(mod_thread_struct);
	if(ret){
		pr_warn("thread ret bad");
	}
	else{
		pr_info("thread ret ok");
	}
}
module_init(mod_init);
module_exit(mod_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sidharth Seela <sidharthseela@gmail.com");
