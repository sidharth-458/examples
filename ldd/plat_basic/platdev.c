#define pr_fmt(fmt) KBUILD_MODNAME ": %s-" fmt "\n" , __func__
#include<linux/module.h>
#include<linux/init.h>
#include<linux/platform_device.h>

static void dev_release(struct device * dev){
	dev = dev;
	pr_info("device released");
}


struct platform_device dev0  = {
	.name = "bitsilica,plat-1x",
	.dev = {
		.release = dev_release,
		.platform_data = "plat-1x", 
	},
};

struct platform_device dev1  = {
	.name = "bitsilica,plat-2x",
	.dev = {
		.release = dev_release,
		.platform_data = "plat-2x",
	},
};


static int __init dev_init(void){
	pr_info("platform device regitering");
	platform_device_register(&dev0);
	platform_device_register(&dev1);	
	return 0;
}

static void __exit dev_exit(void){
	pr_info("platform device unregistering");
	platform_device_unregister(&dev1);
	platform_device_unregister(&dev0);
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
