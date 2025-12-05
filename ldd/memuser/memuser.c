#include<linux/init.h>
#include<linux/module.h>
#include<if.h>

static int __init init(void){
	return vblock_backup_to_file("/root/memuser/log.bin");
}
static void __exit exit(void){
	return;
}
module_init(init);
module_exit(exit);
MODULE_LICENSE("GPL");
