/* user_test.c - test program for the ioctl interface */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "time_if.h"

int main(void)
{
    /*
     * @brief open device
     */
    int fd = open("/dev/time0", O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    int val;
    /*
     * use ioctl to lock increment
     */
    if (ioctl(fd, TIME_LOCK, &val) < 0) {
        perror("TIME_LOCK");
        close(fd);
        return -2;
    }
    close(fd);
    return 0;
}

