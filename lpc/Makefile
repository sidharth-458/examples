
CROSS_COMPILE=arm-none-eabi-
CC=$(CROSS_COMPILE)gcc
LIBC=-L/lib/arm-none-eabi/lib/libc.a -lc
CFLAGS=-Wall -nostdlib -nostartfiles -ffreestanding -mcpu=arm7tdmi -march=armv4t -I include 
all: main.hex

clean:
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf

crt0.o: crt0.S
	$(CROSS_COMPILE)gcc $(CFLAGS) -c crt0.S
	
#main.o : main.c gpio.o timer.o clock.o
#	$(ARMGNU)-gcc $(COPS) -c main.c -o main.o

main.elf : lpc2148.ld crt0.o main.o
	$(CROSS_COMPILE)gcc crt0.o main.o $(CFLAGS) -T lpc2148.ld -o main.elf 

main.bin : main.elf
#	$(ARMGNU)-objcopy main.elf -O binary main.bin

main.hex : main.elf
	$(CROSS_COMPILE)objcopy main.elf -O ihex main.hex

