#include <lpc214x.h>
#include "clock.h"

void CLOCK_INIT(void) 
{
    /*Configure Memory Accelerator Module (MAM) */
    MAMCR  = 0x02;   // Enable MAM
    MAMTIM = 0x04;   // 4 cycles

    /*Enable PLL*/
    PLL0CON = 0x01;   // PLL enable
    PLL0CFG = (5 - 1) | (1 << 5);   // M=5, P=2
    PLL0FEED = 0xAA;  // Feed sequence
    PLL0FEED = 0x55;

    /*Wait for PLL to lock */
    while (!(PLL0STAT & (1 << 10)));  // PLOCK bit

    /*Connect PLL */
    PLL0CON = 0x03;   // Enable + Connect
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;

    /*Set VPBDIV - Peripheral Clock*/
    VPBDIV = 0x01;   // PCLK = CCLK = 60 MHz
		PCONP = 0xFFFFFFFF;
}
