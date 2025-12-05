obj-m:=memuser.o
EXTRA_CFLAGS=-Wall -Werror -I/root/mem/ -Wno-builtin-declaration-mismatch
KBUILD_EXTRA_SYMBOLS=/root/mem/Module.symvers
all:	memuser.c
	${MAKE} -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	${MAKE} -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
