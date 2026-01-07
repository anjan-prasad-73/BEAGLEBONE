#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_gpio.h>   
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>

#define DEVICE_NAME "gpioled"

static int gpio;
static int major;
static struct class *gpio_class;

static ssize_t gpio_write(struct file *f,
                          const char __user *buf,
                          size_t len,
                          loff_t *off)
{
    char kbuf;

    if (copy_from_user(&kbuf, buf, 1))
        return -EFAULT;

    if (kbuf == '1')
        gpio_set_value(gpio, 1);
    else if (kbuf == '0')
        gpio_set_value(gpio, 0);

    return len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .write = gpio_write,
};

static int gpio_probe(struct platform_device *pdev)
{
    int ret;

    pr_info("GPIO LED probe called\n");

    gpio = of_get_named_gpio(pdev->dev.of_node, "gpios", 0);
    if (!gpio_is_valid(gpio)) {
        pr_err("Invalid GPIO\n");
        return -EINVAL;
    }

    ret = gpio_request(gpio, "board_led");
    if (ret)
        return ret;

    gpio_direction_output(gpio, 0);

    major = register_chrdev(0, DEVICE_NAME, &fops);
    gpio_class = class_create(THIS_MODULE, "gpio_class");
    device_create(gpio_class, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);

    pr_info("/dev/%s created\n", DEVICE_NAME);
    return 0;
}

static int gpio_remove(struct platform_device *pdev)
{
    device_destroy(gpio_class, MKDEV(major, 0));
    class_destroy(gpio_class);
    unregister_chrdev(major, DEVICE_NAME);

    gpio_set_value(gpio, 0);
    gpio_free(gpio);

    pr_info("GPIO LED removed\n");
    return 0;
}

static const struct of_device_id gpio_dt_ids[] = {
    { .compatible = "bbblue,board-led" },
    { }
};
MODULE_DEVICE_TABLE(of, gpio_dt_ids);

static struct platform_driver gpio_driver = {
    .probe  = gpio_probe,
    .remove = gpio_remove,
    .driver = {
        .name = "board_led",
        .of_match_table = gpio_dt_ids,
    },
};

module_platform_driver(gpio_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anjan");
MODULE_DESCRIPTION("BeagleBone Blue GPIO LED Driver");

