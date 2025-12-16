obj-m += workq.o
#CFLAGS=-DSTAT
all: workq.c
	${MAKE} -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules EXTRA_CFLAGS+=${CFLAGS}

clean:
	${MAKE} -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
