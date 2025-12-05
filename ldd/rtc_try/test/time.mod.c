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



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xca4b335a, "device_create" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0x15ba50a6, "jiffies" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0xbb9ed3bf, "mutex_trylock" },
	{ 0xf9ca2eb4, "kstrtoint_from_user" },
	{ 0x3213f038, "mutex_unlock" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x656e4a6e, "snprintf" },
	{ 0xa916b694, "strnlen" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x75ca79b5, "__fortify_panic" },
	{ 0x9fa4564a, "timer_shutdown" },
	{ 0xdc0e4855, "timer_delete" },
	{ 0x36bfddc1, "device_destroy" },
	{ 0x73ca058d, "class_destroy" },
	{ 0x37e16a57, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xf926dc9b, "param_ops_int" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x848b9552, "cdev_init" },
	{ 0x3febc5d1, "cdev_add" },
	{ 0x69b07fa1, "class_create" },
	{ 0xbf1981cb, "module_layout" },
};

MODULE_INFO(depends, "");

