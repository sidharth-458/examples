obj-m += temp.o
temp-objs := ts.o fops.o
EXTRA_CFLAGS=-Wall -Werror
all:	ts.c fops.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
