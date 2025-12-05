/*
 * mymain.c
 *
 *  Created on: Nov 20, 2025
 *      Author: sid
 */

#include<stm32l4xx_hal.h>
#include<stdio.h>

#define LED_PIN GPIO_PIN_5
#define LED_PORT GPIOA
#define LED_DELAY 1000

static void led_init(){
	GPIO_InitTypeDef led = {
			.Pin = LED_PIN,
			.Mode = GPIO_MODE_OUTPUT_PP,
	};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(LED_PORT, &led);
}

extern void initialise_monitor_handles();

void my_main(void){
	initialise_monitor_handles();
	int tog = 0;
	HAL_Init();
	printf("hal inited\n");
	led_init();
	while(1){
		HAL_GPIO_WritePin(LED_PORT,LED_PIN,(tog++)%2);
		printf("led toggled\n");
		HAL_Delay(LED_DELAY);
	}
}



