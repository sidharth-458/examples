obj-m += platdrv_dt.o
#time-objs := rtc.o
EXTRA_CFLAGS=-Wall -Werror
all:	platdrv_dt.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
