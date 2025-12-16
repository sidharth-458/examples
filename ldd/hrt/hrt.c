#define pr_fmt(fmt) KBUILD_MODNAME ": %s: " fmt "\n" , __func__
#include<linux/hrtimer.h>
#include<linux/module.h>
#include<linux/ktime.h>
#define PERIOD 1
static struct hrtimer timer = {};
static ktime_t period = {};

static enum hrtimer_restart cb(struct hrtimer * hrt){
	pr_info("%d second elapsed",PERIOD);
	hrtimer_forward_now(hrt,period);
	return HRTIMER_RESTART;
}

static int __init hrt_init(void){
	period = ktime_set(PERIOD,0);
	pr_info("setup");
#ifdef hrtimer_setup
	hrtimer_setup(&timer,cb,CLOCK_MONOTONIC,HRTIMER_MODE_REL);
#else
	hrtimer_init(&timer,CLOCK_MONOTONIC,HRTIMER_MODE_REL);
	timer.function = cb;
#endif
	pr_info("started");
	hrtimer_start(&timer,period,HRTIMER_MODE_REL);
	return 0;
}

static void __exit hrt_exit(void){
	pr_info("cancelled");
	hrtimer_cancel(&timer);
}



module_init(hrt_init);
module_exit(hrt_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SIDHARTH SEELA");
