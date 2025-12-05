obj-m:=memory.o
memory-objs:=mem.o fops.o
EXTRA_CFLAGS=-Wall -Werror
all:	mem.c fops.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
