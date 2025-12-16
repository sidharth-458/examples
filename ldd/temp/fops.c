#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt "\n"
#include<linux/fs.h>
#include<linux/ioctl.h>
#include<linux/poll.h>
#include<linux/atomic.h>
#include"if.h"
/*
static int last_alrts[10];
static atomic_t alert;
*/
static struct ts state = {
			.tmp	= ATOMIC_INIT(0),
			.high	= ATOMIC_INIT(5),
			.low	= ATOMIC_INIT(-13),
			.alrtcnt = ATOMIC_INIT(0),
			.alrtwq = __WAIT_QUEUE_HEAD_INITIALIZER(state.alrtwq)
};

static DECLARE_WAIT_QUEUE_HEAD(wq);

static int ts_open(struct inode *inode, struct file *file){
	pr_info("open");
	return 0;
}
static int ts_release(struct inode *inode, struct file *file){
	pr_info("released");
	return 0;
}
static __poll_t ts_poll(struct file *file, poll_table * p){
	__poll_t mask = 0;
	pr_info("poll wait");
	poll_wait(file,&state.alrtwq,p);
	pr_info("event");
	if(	state.tmp.counter > state.high.counter ||
		state.tmp.counter < state.low.counter	 )
		mask |= POLLPRI;
	if(!mask)
		pr_info("polling going blocking sleep");
	else
		pr_info("mask not empty, will non block alert");
	return mask;
	
}
static long ts_ioctl(struct file * file, unsigned int cmd, unsigned long arg){
        long err = 0;
	switch(cmd){
		case LD_SET_TMP:
			atomic_set(&state.tmp,(int)arg);
			wake_up_interruptible(&state.alrtwq);
		break;
		case LD_SET_HIGH:
			atomic_set(&state.high,(int)arg);
			wake_up_interruptible(&state.alrtwq);
		break;
		case LD_SET_LOW:
			atomic_set(&state.low,(int)arg);
			wake_up_interruptible(&state.alrtwq);
		break;
		case LD_GET_HIST:
		break;
		case LD_GET_ALRT:
		break;
		default:
		break;
	}
	return err;
}




struct file_operations fops ={
	.open = ts_open,
	.release = ts_release,
	.unlocked_ioctl = ts_ioctl,
	.poll = ts_poll,
};
