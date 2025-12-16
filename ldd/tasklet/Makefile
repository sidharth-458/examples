name=tasklet
obj-m += ${name}.o
CFLAGS=-DSTAT
all: ${name}.c
	${MAKE} -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules EXTRA_CFLAGS+=${CFLAGS}

clean:
	${MAKE} -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
