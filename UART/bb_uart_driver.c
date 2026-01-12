#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/serial_core.h>
#include <linux/tty_flip.h>
#include <linux/of.h>

#define DRIVER_NAME "bb_uart"
#define BB_UART_NR 1

static struct uart_driver bb_uart_driver;
static struct uart_port bb_uart_port;

/* ---------- UART OPS ---------- */

static unsigned int bb_uart_tx_empty(struct uart_port *port)
{
    return TIOCSER_TEMT;
}

static void bb_uart_set_mctrl(struct uart_port *port, unsigned int mctrl) {}
static unsigned int bb_uart_get_mctrl(struct uart_port *port)
{
    return TIOCM_CTS | TIOCM_DSR | TIOCM_CAR;
}

static void bb_uart_start_tx(struct uart_port *port) {}
static void bb_uart_stop_tx(struct uart_port *port) {}
static void bb_uart_stop_rx(struct uart_port *port) {}

static int bb_uart_startup(struct uart_port *port)
{
    pr_info("BBB UART startup\n");
    return 0;
}

static void bb_uart_shutdown(struct uart_port *port)
{
    pr_info("BBB UART shutdown\n");
}

static const char *bb_uart_type(struct uart_port *port)
{
    return "bb_uart";
}

static const struct uart_ops bb_uart_ops = {
    .tx_empty = bb_uart_tx_empty,
    .set_mctrl = bb_uart_set_mctrl,
    .get_mctrl = bb_uart_get_mctrl,
    .start_tx = bb_uart_start_tx,
    .stop_tx  = bb_uart_stop_tx,
    .stop_rx  = bb_uart_stop_rx,
    .startup  = bb_uart_startup,
    .shutdown = bb_uart_shutdown,
    .type     = bb_uart_type,
};

/* ---------- PLATFORM DRIVER ---------- */

static int bb_uart_probe(struct platform_device *pdev)
{
    pr_info("BBB UART driver probed\n");

    bb_uart_port.ops = &bb_uart_ops;
    bb_uart_port.line = 0;
    bb_uart_port.type = PORT_16550;
    bb_uart_port.iotype = UPIO_MEM;
    bb_uart_port.fifosize = 16;

    uart_add_one_port(&bb_uart_driver, &bb_uart_port);
    return 0;
}
static void bb_uart_remove(struct platform_device *pdev)
{
    uart_remove_one_port(&bb_uart_driver, &bb_uart_port);
    pr_info("BBB UART driver removed\n");
}


/* ---------- DT MATCH ---------- */

static const struct of_device_id bb_uart_of_match[] = {
    { .compatible = "ti,am3352-uart" },
    { }
};
MODULE_DEVICE_TABLE(of, bb_uart_of_match);

static struct platform_driver bb_uart_platform_driver = {
    .probe  = bb_uart_probe,
    .remove = bb_uart_remove,
    .driver = {
        .name = DRIVER_NAME,
        .of_match_table = bb_uart_of_match,
    },
};

/* ---------- UART DRIVER ---------- */

static struct uart_driver bb_uart_driver = {
    .owner          = THIS_MODULE,
    .driver_name    = DRIVER_NAME,
    .dev_name       = "ttyBB",
    .nr             = BB_UART_NR,
};

/* ---------- INIT / EXIT ---------- */

static int __init bb_uart_init(void)
{
    int ret;

    ret = uart_register_driver(&bb_uart_driver);
    if (ret)
        return ret;

    ret = platform_driver_register(&bb_uart_platform_driver);
    if (ret)
        uart_unregister_driver(&bb_uart_driver);

    return ret;
}

static void __exit bb_uart_exit(void)
{
    platform_driver_unregister(&bb_uart_platform_driver);
    uart_unregister_driver(&bb_uart_driver);
}

module_init(bb_uart_init);
module_exit(bb_uart_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anis");
MODULE_DESCRIPTION("Minimal UART Driver for BeagleBone Black (DT based)");

