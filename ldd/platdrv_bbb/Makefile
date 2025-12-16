obj-m += platdrv_dt.o
#time-objs := rtc.o
EXTRA_CFLAGS=-Wall -Werror
CC_HD=arm-linux-gnueabihf-
ARCH=arm
SRC=/home/sid/Lkd/linux
all:    platdrv_dt.c
	make -C ${SRC} M=$(PWD) ARCH=${ARCH} CROSS_COMPILE=${CC_HD} modules

clean:
	make -C ${SRC} M=$(PWD) ARCH=${ARCH} CROSS_COMPILE=${CC_HD} clean
