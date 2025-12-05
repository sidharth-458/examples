#include <lpc214x.h>
#include "gpio.h"

void GPIO_INIT(void)
{
    //All pins set to GPIO
    PINSEL0 = 0x00000000;
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;

    //All pins as input
    IO0DIR = 0x00000000;
    IO1DIR = 0x00000000;
	
		//Setting Desired Pin 0 as output
		IO0DIR |= (1 << 0);
	
		/*IOxSET, IOxCLR - Can Be used to Set State (HIGH, LOW)*/
		IO0SET = (1 << 0);
}
