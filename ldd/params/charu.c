#define pr_fmt(fmt) KBUILD_MODNAME": "fmt"\n"
#include<linux/init.h>		/* for __init,__exit,THIS_MODULE*/
#include<linux/module.h>	/* for module_init(), module_exit()*/

static int arr[10];
static int arr_count;
static int __init charu_init(void){
	for(int i = 0; i<10;i++){
		pr_info("arr[%d] is %d",i,arr[i]);
	}
	pr_info("arr_count is %d",arr_count);
	return 0;
}

static void __exit charu_exit(void){
	pr_info("exit");
}

MODULE_AUTHOR("Sidharth Seela<sidharthseela@gmail.com");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple characted device");
module_init(charu_init);
module_exit(charu_exit);
module_param_array(arr,int,&arr_count, 0644);
MODULE_PARM_DESC(arr,"an integer array");

