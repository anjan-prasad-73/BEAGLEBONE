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
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0xadfaa6f6, "__platform_driver_register" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x31772c7d, "gpio_to_desc" },
	{ 0x7b70a77b, "gpiod_set_raw_value" },
	{ 0xfe990052, "gpio_free" },
	{ 0x81b33603, "device_destroy" },
	{ 0x10767ee6, "class_destroy" },
	{ 0xf8ace47c, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x92997ed8, "_printk" },
	{ 0x3992149a, "platform_driver_unregister" },
	{ 0xac4edd31, "of_get_named_gpio" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x2840ffb3, "gpiod_direction_output_raw" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x31467da, "cdev_init" },
	{ 0x70099524, "cdev_add" },
	{ 0x7bfd158, "class_create" },
	{ 0x31ebf0af, "device_create" },
	{ 0x8b6bd5aa, "_dev_info" },
	{ 0xcae6408a, "_dev_err" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xbc3b8546, "__fortify_panic" },
	{ 0x31916f86, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cbbblue,my-led");
MODULE_ALIAS("of:N*T*Cbbblue,my-ledC*");
