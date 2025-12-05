obj-m += charu.o
EXTRA_CFLAGS=-Wall -Werror
all:	charu.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
