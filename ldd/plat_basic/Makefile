obj-m += platdrv.o platdev.o
#time-objs := rtc.o
EXTRA_CFLAGS=-Wall -Werror
all:	platdrv.c platdev.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
