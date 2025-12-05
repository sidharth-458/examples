#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt "\n"
#include<linux/init.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/kthread.h>
#include<linux/delay.h>

int calc_add(int a,int b);

int calc_add(int a, int b){
	return a+b;
}
EXPORT_SYMBOL(calc_add);

__init static int mod_init(void){
	pr_info("calc available");
	return 0;
}

__exit static void mod_exit(void){
	pr_info("calc exit");
}
module_init(mod_init);
module_exit(mod_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sidharth Seela <sidharthseela@gmail.com");
