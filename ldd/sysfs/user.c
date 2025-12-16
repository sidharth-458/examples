/* user_test.c - test program for the ioctl interface */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "chard_if.h"

int main(void)
{
    int fd = open("/dev/charu0", O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    int val;
    if (ioctl(fd, CHARD_UNLOCK, &val) < 0) {
        perror("CHARD_UNLOCK");
        close(fd);
        return 1;
    }

    /* Read it back */
    val = 1024;
    if (ioctl(fd, CHARD_BUFF_SIZE, &val) < 0) {
        perror("CHARD_BUFF_SIZE");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}

