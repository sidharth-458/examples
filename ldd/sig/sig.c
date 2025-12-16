#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/kthread.h>
#include <linux/delay.h>


struct task_struct *thread1;

static int inc_thread(void *data)
{
	int i = 0;
	allow_signal(SIGINT);
	printk("Thread Started,waiting for signal\n");
	unsigned long remains = msleep_interruptible(10000);
	if(remains)
		pr_info("thread encountered signal");
	printk("Thread completed remainder was %lu\n",remains);
	 return 0;
}

MODULE_LICENSE("GPL");
static int __init test_tasks_init(void)
{
    thread1 = kthread_run(inc_thread, NULL,"thread1");
    msleep_interruptible(3000);
	send_sig(SIGINT,thread1,0);
    return 0;
}

static void __exit test_tasks_exit(void)
{
}

module_init(test_tasks_init);
module_exit(test_tasks_exit);
