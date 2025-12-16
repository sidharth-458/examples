#define pr_fmt(fmt) KBUILD_MODNAME ": %s-" fmt "\n" , __func__
#include<linux/module.h>
#include<linux/init.h>
#include<linux/platform_device.h>
#include<linux/mod_devicetable.h>
static int drv_probe(struct platform_device * dev){
	pr_info("probed %s",(char *)dev_get_platdata(&dev->dev));
	return 0;
}
static void drv_remove(struct platform_device * dev){
	pr_info("removed %s",(char *)dev_get_platdata(&dev->dev));
}
static struct platform_device_id dev_ids[] = {
	[0] = {	.name = "bitsilica,plat-1x"},
	[1] = {	.name = "bitsilica,plat-2x"},
};
struct platform_driver drv  = {
	.probe = drv_probe,
	.remove = drv_remove,
	.id_table = dev_ids,
	.driver = {
		.name = "plat-nx-driver"
	},
};


static int __init drv_init(void){
	pr_info("platform driver regitering");
	platform_driver_register(&drv);
	return 0;
}

static void __exit drv_exit(void){
	pr_info("platform driver unregistering");
	platform_driver_unregister(&drv);
}

module_init(drv_init);
module_exit(drv_exit);
MODULE_LICENSE("GPL");
