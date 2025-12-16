#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt "\n"
#include<linux/init.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/kthread.h>
#include<linux/delay.h>
#include<linux/list.h>

struct data{
	struct list_head list;
	int info;
};

static int __init mod_init(void){
	pr_info("list entry");

	struct list_head head;
	INIT_LIST_HEAD(&head);

	struct data d0 = {{},0};
	list_add(&d0.list,&head);
	
	struct data d1 = {{},1};
	list_add(&d1.list,&head);
	
	struct data * pnode;
	list_for_each_entry(pnode,&head,list){
		pr_info("%d",pnode->info);
	}
	return 0;
}

static void __exit mod_exit(void){
	pr_info("list exit");
}
module_init(mod_init);
module_exit(mod_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sidharth Seela <sidharthseela@gmail.com");
