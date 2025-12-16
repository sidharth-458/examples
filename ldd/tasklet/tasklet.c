#define pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt "\n", __func__
#include<linux/module.h>
#include<linux/interrupt.h>

static void tl_fn(struct tasklet_struct *){
	pr_info("tl ran");
}
#ifdef STAT
	DECLARE_TASKLET(tl,tl_fn);
#else
	static struct tl;
#endif

static int __init workq_init(void){
	pr_info("init");
#ifdef STAT
#else
	tasklet_setup(&tl,tl_fn)
#endif
	tasklet_schedule(&tl);
	return 0;
}
static void __exit workq_exit(void){
	pr_info("exit");
}

module_init(workq_init);
module_exit(workq_exit);
MODULE_LICENSE("GPL");

