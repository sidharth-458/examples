#define pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt "\n", __func__
#include<linux/module.h>
#include<linux/workqueue.h>

static void workq_fn(struct work_struct * work){
	pr_info("work queue ran");
}
#ifdef STAT
	DECLARE_WORK(workqueue,workq_fn);
#else
	static struct work_struct workqueue;
#endif

static int __init workq_init(void){
	pr_info("init");
#ifdef STAT
#else
	INIT_WORK(&workqueue,workq_fn);	
#endif
	schedule_work(&workqueue);
	return 0;
}
static void __exit workq_exit(void){
	pr_info("exit");
}

module_init(workq_init);
module_exit(workq_exit);
MODULE_LICENSE("GPL");

