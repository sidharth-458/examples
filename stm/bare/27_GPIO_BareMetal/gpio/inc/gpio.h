#ifndef GPIO_H
#define GPIO_H
#include<stm32f476xx.h>

void GPIOA_Init();

void GPIOA_SetOut(uint8_t pin_no);
void GPIOA_High(uint8_t pin);

void GPIO_Low(uint8_t pin);

#endif
