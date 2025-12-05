/*
 * mymain.c
 *
 *  Created on: Nov 20, 2025
 *      Author: sid
 */


#include<stm32l4xx_hal.h>

#define LED_PIN GPIO_PIN_5
#define LED_PORT GPIOA
#define LED_DELAY 1000

#define SYSTICK_LOAD (SystemCoreClock/1000000U)

//40 counts in usec
#define DELAY_US(us) \
    do { \
         uint32_t start = SysTick->VAL; \
         uint32_t ticks = us * SYSTICK_LOAD; \
         while((start - SysTick->VAL) < ticks); \
    } while (0)
#define DELAY_MS(ms) \
	do{\
		for(int i = 0; i<ms; i++)\
			DELAY_US(ms);\
	}while(0)

static void led_init(){
	GPIO_InitTypeDef led = {
			.Pin = LED_PIN,
			.Mode = GPIO_MODE_OUTPUT_PP,
	};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(LED_PORT, &led);
}

void my_main(void){
	int tog = 0;
	HAL_Init();
	led_init();
	while(1){
		HAL_GPIO_WritePin(LED_PORT,LED_PIN,(tog++)%2);
		DELAY_MS(1000);

	}
}

