obj-m += time.o
time-objs := rtc.o
EXTRA_CFLAGS=-Wall -Werror
all:	rtc.c fops.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
