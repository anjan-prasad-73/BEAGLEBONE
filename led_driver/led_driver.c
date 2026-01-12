#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#define DEV_NAME "bbblue_led"

static dev_t devno;
static struct cdev led_cdev;
static struct class *led_class;
static int led_gpio;

/* Write operation */
static ssize_t led_write(struct file *f, const char __user *buf,
                         size_t len, loff_t *off)
{
    char kbuf;

    if (copy_from_user(&kbuf, buf, 1))
        return -EFAULT;

    gpio_set_value(led_gpio, (kbuf == '1') ? 1 : 0);
    return len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .write = led_write,
};

static int bbblue_led_probe(struct platform_device *pdev)
{
    struct device *dev = &pdev->dev;

    led_gpio = of_get_named_gpio(dev->of_node, "gpios", 0);
    if (!gpio_is_valid(led_gpio)) {
        dev_err(dev, "Invalid GPIO\n");
        return -EINVAL;
    }

    gpio_request(led_gpio, "bbblue_led");
    gpio_direction_output(led_gpio, 0);

    alloc_chrdev_region(&devno, 0, 1, DEV_NAME);
    cdev_init(&led_cdev, &fops);
    cdev_add(&led_cdev, devno, 1);

    led_class = class_create( DEV_NAME);
    device_create(led_class, NULL, devno, NULL, DEV_NAME);

    dev_info(dev, "BBBlue LED driver loaded\n");
    return 0;
}

static void bbblue_led_remove(struct platform_device *pdev)
{
    gpio_set_value(led_gpio, 0);
    gpio_free(led_gpio);

    device_destroy(led_class, devno);
    class_destroy(led_class);
    cdev_del(&led_cdev);
    unregister_chrdev_region(devno, 1);

    pr_info("BBBlue LED driver removed\n");

}

static const struct of_device_id led_of_match[] = {
    { .compatible = "bbblue,my-led" },
    { }
};
MODULE_DEVICE_TABLE(of, led_of_match);

static struct platform_driver bbblue_led_driver = {
    .probe  = bbblue_led_probe,
    .remove = bbblue_led_remove,
    .driver = {
        .name = "bbblue_led",
        .of_match_table = led_of_match,
    },
};

module_platform_driver(bbblue_led_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anjan");
MODULE_DESCRIPTION("BeagleBone Blue LED Driver");
