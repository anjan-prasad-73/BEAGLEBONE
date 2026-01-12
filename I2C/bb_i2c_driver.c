#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/i2c.h>

#define DRIVER_NAME "bb_i2c_driver"

static struct i2c_client *bb_client;

/* ---------- I2C Write ---------- */
static int bb_i2c_write(u8 reg, u8 val)
{
    return i2c_smbus_write_byte_data(bb_client, reg, val);
}

/* ---------- I2C Read ---------- */
static int bb_i2c_read(u8 reg, u8 *val)
{
    int ret;

    ret = i2c_smbus_read_byte_data(bb_client, reg);
    if (ret < 0)
        return ret;

    *val = ret & 0xFF;
    return 0;
}

/* ---------- PROBE (Linux 6.x) ---------- */
static int bb_i2c_probe(struct i2c_client *client)
{
    u8 value;

    pr_info("BBB I2C driver probed (kernel 6.x)\n");
    bb_client = client;

    bb_i2c_write(0x01, 0xAA);
    bb_i2c_read(0x01, &value);

    pr_info("Read value = 0x%x\n", value);
    return 0;
}

/* ---------- REMOVE (Linux 6.x) ---------- */
static void bb_i2c_remove(struct i2c_client *client)
{
    pr_info("BBB I2C driver removed\n");
}

/* ---------- Device Tree Match ---------- */
static const struct of_device_id bb_i2c_of_match[] = {
    { .compatible = "bb,my-i2c-dev" },
    { }
};
MODULE_DEVICE_TABLE(of, bb_i2c_of_match);

/* ---------- I2C Driver ---------- */
static struct i2c_driver bb_i2c_driver = {
    .driver = {
        .name = DRIVER_NAME,
        .of_match_table = bb_i2c_of_match,
    },
    .probe  = bb_i2c_probe,
    .remove = bb_i2c_remove,
};

/* ---------- Register Driver ---------- */
module_i2c_driver(bb_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anis");
MODULE_DESCRIPTION("I2C driver for BeagleBone Black (Linux 6.x)");
