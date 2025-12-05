obj-m += proc.o

all: proc.c
	${MAKE} -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	${MAKE} -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
