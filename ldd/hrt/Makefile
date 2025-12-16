obj-m += hrt.o
EXTRA_CFLAGS=-Wall -Werror
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) EXTRA_CFLAGS=${EXTRA_CFLAGS} modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
