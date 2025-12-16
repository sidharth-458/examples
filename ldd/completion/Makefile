name = comp
obj-m += ${name}.o
EXTRA_CFLAGS=-Wall -Werror
all: ${name}.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) EXTRA_CFLAGS=${EXTRA_CFLAGS} modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
