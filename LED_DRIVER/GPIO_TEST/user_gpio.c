#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;

    if (argc != 2) {
        printf("Usage: %s <0|1>\n", argv[0]);
        return 1;
    }

    fd = open("/dev/gpioled", O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    write(fd, argv[1], 1);
    close(fd);

    return 0;
}

