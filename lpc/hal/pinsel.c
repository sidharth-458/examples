#include"hal.h"
static uint32_t * pinsels[] = {&PINSEL0,&PINSEL1,&PINSEL2};

void pinsel(struct s_pinsel pin){
	if(pin.bank > 2)
		assert(0);
	
	*pinsels[pin.bank] = *pinsels[pin.bank] & ~(3<<pin.pin);
	*pinsels[pin.bank] = *pinsels[pin.bank] | (pin.mode<<pin.pin);
}
