#include<gpio.h>

void GPIOA_Init(){
	GPIOA_CLK_EN();
}

void GPIOA_SetOut(uint8_t pin_no){
	GPIOA->MODER &= ~(1<< (2 * pin_no + 1));
	//GPIOA->OTYPER|= 1<<pin_no;
}

void GPIOA_High(uint8_t pin){
	GPIOA->ODR |= 1<<pin;
}

void GPIO_Low(uint8_t pin){
	GPIOA->ODR &= ~(1<<pin);
}


