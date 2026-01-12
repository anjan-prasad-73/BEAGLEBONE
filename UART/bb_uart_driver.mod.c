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
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x39704a2d, "uart_register_driver" },
	{ 0xadfaa6f6, "__platform_driver_register" },
	{ 0xfcbe1976, "uart_unregister_driver" },
	{ 0x56cc125d, "uart_remove_one_port" },
	{ 0x92997ed8, "_printk" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x39096de5, "uart_add_one_port" },
	{ 0x3992149a, "platform_driver_unregister" },
	{ 0x31916f86, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cti,am3352-uart");
MODULE_ALIAS("of:N*T*Cti,am3352-uartC*");
