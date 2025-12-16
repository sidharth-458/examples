#define pr_fmt(fmt) KBUILD_MODNAME ": %s-" fmt "\n" , __func__
#include<linux/module.h>
#include<linux/init.h>
#include<linux/platform_device.h>
#include<linux/mod_devicetable.h>
#include<linux/of.h>
#include<linux/of_device.h>
#include<linux/slab.h>
struct s_plat_1x{
        int baud;
};
struct s_plat_2x{
        int baud;
        int parity;
};

static struct of_device_id dev_ids[] = {
        {.compatible = "bitsilica,plat-1x",.data=(void*)0},
        {.compatible = "bitsilica,plat-2x",.data=(void*)1},
        {}
};

static ssize_t baud_show(struct device * dev,struct device_attribute *attr, char *buf){
	struct s_plat_1x * p = dev_get_drvdata(dev);
	return sprintf(buf,"%d\n",p->baud);
}

static ssize_t parity_show(struct device * dev,struct device_attribute *attr, char *buf){
	struct s_plat_2x * p = dev_get_drvdata(dev);
	return sprintf(buf,"%d\n",p->parity);
}
static DEVICE_ATTR_RO(baud);
static DEVICE_ATTR_RO(parity);

static int drv_probe(struct platform_device * dev){
        pr_info("probed");
	struct device_node *dev_node = dev->dev.of_node;
	if(!dev_node){
		pr_err("no of dt data found");
		return 0;
	}
	const struct of_device_id * match = of_match_device(dev->dev.driver->of_match_table,&dev->dev);
	u32 val;
	switch((int)match->data){
		case 0:{
			pr_info("of 0");
			struct s_plat_1x * p1 = kzalloc(sizeof(*p1), GFP_KERNEL);
			if(!p1)
				pr_err("kzalloc failed");
			of_property_read_u32_index(dev_node,"bitsilica,baud",0,&val);
			p1->baud = val;
			pr_info("baud is %d",val);
			dev_set_drvdata(&dev->dev,p1);
			sysfs_create_file(&dev->dev.kobj,&dev_attr_baud.attr);
		       }
			break;
		case 1:
			{
			pr_info("of 1");
			struct s_plat_2x *p2  = kzalloc(sizeof(*p2), GFP_KERNEL);
			if(!p2)
				pr_err("kzalloc failed");
			of_property_read_u32_index(dev_node,"bitsilica,baud",0,&val);
			p2->baud = val;
			pr_info("baud is %d",val);
			of_property_read_u32_index(dev_node,"bitsilica,parity",0,&val);
			p2->parity = val;
			pr_info("parity is %d",val);
			dev_set_drvdata(&dev->dev,p2);
			sysfs_create_file(&dev->dev.kobj,&dev_attr_baud.attr);
			sysfs_create_file(&dev->dev.kobj,&dev_attr_parity.attr);
			}
			break;
		default:
			pr_err("of match details failure");
			break;
	}

        return 0;
}
static void drv_remove(struct platform_device * dev){
        pr_info("removed");
	kfree(dev_get_drvdata(&dev->dev));
	dev_set_drvdata(&dev->dev,0);
	struct device_node *dev_node = dev->dev.of_node;
	if(!dev_node){
		pr_err("no of dt data found");
		return;
	}
	const struct of_device_id * match = of_match_device(dev->dev.driver->of_match_table,&dev->dev);
	u32 val;
	switch((int)match->data){
		case 0:
			sysfs_remove_file(&dev->dev.kobj,&dev_attr_baud.attr);
			break;
		case 1:
			sysfs_remove_file(&dev->dev.kobj,&dev_attr_baud.attr);
			sysfs_remove_file(&dev->dev.kobj,&dev_attr_parity.attr);
			break;
		default:
			break;
	}
}
/*static struct platform_device_id dev_ids[] = {
        [0] = { .name = "bitsilica,plat-1x"},
        [1] = { .name = "bitsilica,plat-2x"},
};
*/

struct platform_driver drv  = {
        .probe = drv_probe,
        .remove = drv_remove,
        //.id_table = dev_ids,
        .driver = {
                .name = "plat-nx-driver",
                .of_match_table = of_match_ptr(dev_ids),
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
