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
	{ 0x998bc01a, "__spi_register_driver" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x92997ed8, "_printk" },
	{ 0x5f754e5a, "memset" },
	{ 0x7696f8c7, "__list_add_valid_or_report" },
	{ 0x4ce511fc, "spi_sync" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x65e7a1c3, "spi_setup" },
	{ 0xa5fe824f, "driver_unregister" },
	{ 0x31916f86, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cbb,spi-device");
MODULE_ALIAS("of:N*T*Cbb,spi-deviceC*");
