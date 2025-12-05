#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt "\n"
#include<linux/init.h>
#include<linux/module.h>
extern int calc_add(int,int);
__init static int mod_init(void){
	int sum = calc_add(4,5);
	pr_info("entry user %d",sum);
	return 0;
}

__exit static void mod_exit(void){
	pr_info("exit user");
}
module_init(mod_init);
module_exit(mod_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sidharth Seela <sidharthseela@gmail.com");
