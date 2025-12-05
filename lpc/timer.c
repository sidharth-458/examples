#include <lpc214x.h>
#include "timer.h"

_Bool LED_State = 1;

__attribute__ ((interrupt ("IRQ"))) void Timer0_ISR(void)
{	
		//Toggle LED
		LED_State ^= 1;
	
		if (LED_State)
		{
			IO0SET = (1 << 0);
		}
		else
		{
			IO0CLR = (1 << 0);
		}
	
    // Clear Timer0 interrupt flag
    T0IR = 0x01;

    // Acknowledge interrupt to VIC
    VICVectAddr = 0x00;
}

void TIMER_ISR_INIT(void)
{
		T0TCR = 0x02;          			// Reset Timer0
    T0PR  = TIMER_PERIOD_MS(1);  	// Prescaler (PCLK = 60 MHz)
    T0TC  = 0;			   			// Reset Counter
		T0MR0 = 1000;          // 1000 Counts
		T0MCR = 	(1 << 0)       // Interrupt on MR0
						| (1 << 1)       // Reset on MR0
						| (0 << 2);      // No stop
		T0IR = 0x01;           // Clear interrupt flag for MR0
		T0TCR = 0x01;          // Enable Timer0
	
    VICIntSelect &= ~(1 << 4);              // Timer0 = IRQ (not FIQ)
    VICVectAddr1 = (unsigned long)Timer0_ISR; // ISR address
    VICVectCntl1 = (1 << 5) | 4;            // enable slot 1, source=Timer0 (IRQ #4)
    VICIntEnable = (1 << 4);                // enable Timer0 interrupt
}
