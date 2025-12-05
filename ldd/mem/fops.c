#include<linux/fs.h>
#include<linux/moduleparam.h>
#include<linux/ioctl.h>
#include"if.h"
/* configuration */
static int keys[10] = {0};
static int keycount = 0;
module_param_array(keys,int,&keycount,S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(keys,"Comma seperated integer keys of 10 elements");

static bool is_cp = false;
module_param(is_cp,bool,S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(is_cp,"Do create copy of buffers or not");

/*TODO:mutex */

/*buffers*/
static unsigned char memlock = 0;
static char mem[4096] = {0};
static char memcp[4096] = {0};
/*fops*/
static bool isAuth(int key){
	bool ret = false;
	for(int i =0;i<keycount;i++){
		if(keys[i] == key){
			ret = true;
			goto end;
		}
	}
end:
	return ret;
}
static bool isByteLocked(loff_t offset){
	int sector = offset/512;
	if(memlock & 1<<sector)
		return true;
	else
		return false;
}
static ssize_t mem_write(struct file * file, const char __user * buff,size_t len, loff_t * off){
	//bool verified = false;
	ssize_t ret;
	struct w_hd header;
	bool auth = false;
	pr_info("%zd %zd",len,sizeof(struct w_hd));
	if(len < sizeof(struct w_hd) || len > 4096 + sizeof(struct w_hd)){
		pr_err("len is invalid"); 
		ret = -EINVAL;
		goto end;
	}
	if(copy_from_user((void*)&header,(void*)buff,sizeof(struct w_hd))){
		pr_err("header copy error");
		ret = -EPERM;
		goto end;
	}
	len -= sizeof(struct w_hd);
	buff += sizeof(struct w_hd);
	loff_t fakeset = *off;
	*off = header.offset;
	auth = isAuth(header.key);
	/*TODO: CHECK FOR EXCESS LEN OR OFFSET*/
		
	ret = len;
	for(int i = 0;i<len;i++){
		if(isByteLocked(*off)){
			if(auth){
				/*then write*/
				if(copy_from_user((void*)mem + *off,(void*)(buff + fakeset),1)){
					pr_err("body copy error");
					ret = -EPERM;
					goto end;
				}
				if(is_cp){
					if(copy_from_user((void*)memcp + *off,(void*)(buff + fakeset),1)){
						pr_err("body copy error to cpbuff");
					}
				}
			}
		}
		else{
			if(copy_from_user((void*)mem + *off,(void*)(buff + fakeset),1)){
				pr_err("body copy error");
				ret = -EPERM;
				goto end;
			}
			if(is_cp){
				if(copy_from_user((void*)memcp + *off,(void*)(buff + fakeset),1)){
					pr_err("body copy error to cpbuff");
				}
			}
			/*write*/
		}
		(*off)++;
		fakeset++;
	}

end:
	return ret;
}

static ssize_t mem_read(struct file * file, char __user * user,size_t len, loff_t * off){
	ssize_t ret;
	if(*off > 4096){
		ret = -ENOMEM;
		goto end;
	}

	if(*off + len > 4096)
		len = 4096 - *off;

	if(0 != copy_to_user(user,mem + *off,len)){
		ret = -EPERM;
		goto end;
	}

	ret = len;
	*off+=len;
end:
	return ret;
}

static long mem_ioctl(struct file * file, unsigned int cmd, unsigned long arg){
	long err = 0;
	struct region * reg;
	unsigned char regnum = 0;
	unsigned char* lockmap ;
	switch(cmd){
		case VBLOCK_LOCK_REGION:
			if(arg >= 1 && arg <=8){
				memlock = memlock | (1<<(arg - 1));
				pr_info("ioctl: memlock val %x",memlock);
			}
			else{
				err = -EINVAL;
				pr_err("ioctl: invalid region num");
			}
			break;
		case VBLOCK_UNLOCK_REGION:
			if(arg >= 1 && arg <=8){
				memlock = memlock & ~(1<<(arg -1));
				pr_info("ioctl: memlock val %x",memlock);
			}
			else{
				err = -EINVAL;
				pr_err("ioctl: invalid region num");
			}
			break;
		case VBLOCK_READ_REGION:
			reg = (struct region *) arg;
			if(copy_from_user(&regnum,&reg->num,1)){
				err = -EINVAL;
				pr_err("ioctl: invalid pointer to struct region");
				break;
			}
			if(regnum >= 1 && regnum <=8){
				pr_info("ioctl: read %d region",regnum);
				if(copy_to_user(reg->data,mem + 512 * (regnum - 1),512)){
					err = -EINVAL;
					pr_err("ioctl: failed copy_to_user");
					break;
				}
			}
			else{
				err = -EINVAL;
				pr_err("ioctl: invalid region num");
			}
			break;
		case VBLOCK_GET_INFO:
			lockmap = (unsigned char *) arg;
			if(copy_to_user(lockmap,&memlock,1)){
				err = -EINVAL;
				pr_err("ioctl: invalid pointer to char *");
			}
			pr_info("ioctl: given memlock back");
			break; 
		case VBLOCK_ERASE_REGION:
			if(!(arg >= 1 && arg <= 8)){
				err = -EINVAL;
				pr_err("ioctl: invalid region num");
				break;
			}
			memset(mem + 512 * (arg - 1),0,512);
			memset(memcp + 512 * (arg - 1), 0, 512);
			pr_info("ioctl: memset region %d",(char)arg);
			break;
		default:
			break;
	}
	return err;
}



struct file_operations fops ={
	.write = mem_write,
	.read = mem_read,
	.unlocked_ioctl = mem_ioctl,
	.llseek = default_llseek,
	.owner = THIS_MODULE,
};

int vblock_backup_to_file(const char *path){
	struct file * fp;
	fp = filp_open(path,O_WRONLY | O_CREAT,0644);
	if(IS_ERR(fp)){
		pr_err("file open error");
		return -E2BIG;
	}

	if(4096 != kernel_write(fp,memcp,4096,0)){
		pr_err("exported less");
	}
	filp_close(fp,NULL);
	return 0;
}
EXPORT_SYMBOL(vblock_backup_to_file);

