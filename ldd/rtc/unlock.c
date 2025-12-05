/* user_test.c - test program for the ioctl interface */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "time_if.h"

int main(void)
{
    int fd = open("/dev/time0", O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    int val;

    /* @brief use ioctl to unlock device */
    if (ioctl(fd,TIME_UNLOCK, &val) < 0) {
        perror("TIME_UNLOCK");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}

