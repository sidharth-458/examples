#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

KSYMTAB_FUNC(vblock_backup_to_file, "", "");

SYMBOL_CRC(vblock_backup_to_file, 0x56ce2cb8, "");

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x73ca058d, "class_destroy" },
	{ 0x138f872d, "param_array_ops" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x92997ed8, "_printk" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x3febc5d1, "cdev_add" },
	{ 0xca4b335a, "device_create" },
	{ 0x69b07fa1, "class_create" },
	{ 0xb540ed99, "default_llseek" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xd9bb9b9, "param_ops_bool" },
	{ 0xee923e42, "filp_close" },
	{ 0x36bfddc1, "device_destroy" },
	{ 0xf926dc9b, "param_ops_int" },
	{ 0x848b9552, "cdev_init" },
	{ 0x37e16a57, "cdev_del" },
	{ 0x43276891, "kernel_write" },
	{ 0x946a5f30, "filp_open" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0xbf1981cb, "module_layout" },
};

MODULE_INFO(depends, "");

