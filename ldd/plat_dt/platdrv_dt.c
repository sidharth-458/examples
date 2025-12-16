#define pr_fmt(fmt) KBUILD_MODNAME ": %s-" fmt "\n" , __func__
#include<linux/module.h>
#include<linux/init.h>
#include<linux/platform_device.h>
#include<linux/mod_devicetable.h>
#include<linux/of.h>
static struct s_plat_1x{
	int baud;
}plat_1x = { .baud = 9600};
static struct s_plat_2x{
	int baud;
	int parity;
}plat_2x = {.baud = 9600, .parity = 0};


static int drv_probe(struct platform_device * dev){
	pr_info("probed");
	return 0;
}
static void drv_remove(struct platform_device * dev){
	pr_info("removed");
}
/*static struct platform_device_id dev_ids[] = {
	[0] = {	.name = "bitsilica,plat-1x"},
	[1] = {	.name = "bitsilica,plat-2x"},
};
*/
static struct of_device_id dev_ids[] = {
	{.compatible = "bitsilica,plat-1x",.data=(void*)&plat_1x},
	{.compatible = "bitsilica,plat-2x",.data=(void*)&plat_2x},
	{}
};
struct platform_driver drv  = {
	.probe = drv_probe,
	.remove = drv_remove,
	//.id_table = dev_ids,
	.driver = {
		.name = "plat-nx-driver",
		.of_match_table = dev_ids,
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
