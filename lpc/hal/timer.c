#include"hal.h"
static uint32_t * t0[] = {&T0CTCR,&T0PR,&T0TC,&T0TCR,&T0TC};
static uint32_t * t1[] = {&T1CTCR,&T1PR,&T1TC,&T1TCR,&T1TC};

enum{
	CONFIGURE,
	PRESCALE,
	RESET,
	STARTSTOP,
	BUFFER,
};

void delay(uint8_t timernum, uint32_t div, uint32_t reps){
	uint32_t *** t;
	if(!div)
		assert(0);
	t = timernum ? t1:t0;
	
	*t[CONFIGURE] = TIMER;

	*t[PRESCALE] = div;

	*t[RESET] = 0;

	*t[STARTSTOP] = 1;

	while(*t[BUFFER] < reps);

	*t[STARTSTOP] = 0;
}
