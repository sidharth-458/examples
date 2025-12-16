obj-m += lightdev.o
lightdev-objs := slc.o fops.o
EXTRA_CFLAGS=-Wall -Werror
all:	slc.c fops.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
