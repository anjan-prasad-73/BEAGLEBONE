#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spi/spi.h>

static struct spi_device *bb_spi;

/* ---------- SPI TRANSFER ---------- */
static int bb_spi_transfer(void)
{
    u8 tx[2] = {0x9F, 0x00};
    u8 rx[2] = {0};

    struct spi_transfer t = {
        .tx_buf = tx,
        .rx_buf = rx,
        .len = 2,
        .speed_hz = 1000000,
    };

    struct spi_message m;
    spi_message_init(&m);
    spi_message_add_tail(&t, &m);

    return spi_sync(bb_spi, &m);
}

/* ---------- PROBE ---------- */
static int bb_spi_probe(struct spi_device *spi)
{
    int ret;

    pr_info("BBB SPI driver probed (DT based)\n");

    bb_spi = spi;

    spi->mode = SPI_MODE_0;
    spi->bits_per_word = 8;
    spi->max_speed_hz = 1000000;

    ret = spi_setup(spi);
    if (ret)
        return ret;

    bb_spi_transfer();
    return 0;
}

/* ---------- REMOVE ---------- */
static void bb_spi_remove(struct spi_device *spi)
{
    pr_info("BBB SPI driver removed\n");
}

/* ---------- DT MATCH ---------- */
static const struct of_device_id bb_spi_of_match[] = {
    { .compatible = "bb,spi-device" },
    { }
};
MODULE_DEVICE_TABLE(of, bb_spi_of_match);

/* ---------- SPI DRIVER ---------- */
static struct spi_driver bb_spi_driver = {
    .driver = {
        .name = "bb_spi_driver",
        .of_match_table = bb_spi_of_match,
    },
    .probe  = bb_spi_probe,
    .remove = bb_spi_remove,
};

module_spi_driver(bb_spi_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anis");
MODULE_DESCRIPTION("SPI driver for BeagleBone Black using Device Tree");

