obj-m += bmod.o
EXTRA_CFLAGS=-Wall -Werror
KBUILD_EXTRA_SYMBOLS=/root/amod/Module.symvers
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
