#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt "\n"
#include<linux/fs.h>
#include<linux/moduleparam.h>
#include<linux/ioctl.h>
#include"if.h"

static struct ld_state state = {
				.brt	= ATOMIC_INIT(0),
				.tmp	= ATOMIC_INIT(2000),
				.usrs	= ATOMIC_INIT(0),
				.on	= ATOMIC_INIT(0) };

static int ld_open(struct inode *inode, struct file *file){
	atomic_inc(&state.usrs);
	return 0;
}
static int ld_release(struct inode *inode, struct file *file){
	atomic_dec(&state.usrs);
	return 0;
}
static long ld_ioctl(struct file * file, unsigned int cmd, unsigned long arg){
        long err = 0;
        switch(cmd){
        	case LD_SET_ON:
			atomic_set(&state.on,1);
		break;
		case LD_SET_OFF:
			atomic_set(&state.on,0);
		break;
		case LD_SET_BRT:
		{
			int brt = (int)arg;
			if(0 < brt && brt <= 100)
				atomic_set(&state.brt,brt);
		}
		break;
		case LD_SET_TMP:
		{
			int tmp = (int)arg;
			if(2000 < tmp && tmp <= 6500)
				atomic_set(&state.tmp,tmp);
		}
		break;
		case LD_GET_STATE:
			if(copy_to_user((void *)arg,(void*)&state,sizeof(state))){
				pr_err("copy_to_user failed");
				err = -1;
			}
		break;
		default:
			err = -1;
			break;
	}
        return err;
}




struct file_operations fops ={
	.open = ld_open,
	.release = ld_release,
	.unlocked_ioctl = ld_ioctl,
};
