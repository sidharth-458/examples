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

#define BTN_PIN GPIO_PIN_13
#define BTN_PORT GPIOC


static void led_init(){
	GPIO_InitTypeDef led = {
			.Pin = LED_PIN,
			.Mode = GPIO_MODE_OUTPUT_PP,
	};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(LED_PORT, &led);
}
static void btn_init(){
	GPIO_InitTypeDef btn = {
			.Pin = BTN_PIN,
			.Mode = GPIO_MODE_INPUT,
	};
	__HAL_RCC_GPIOC_CLK_ENABLE();
	HAL_GPIO_Init(BTN_PORT, &btn);
}

void my_main(void){
	HAL_Init();
	led_init();
	btn_init();
	while(1){
		HAL_GPIO_WritePin(LED_PORT,LED_PIN,HAL_GPIO_ReadPin(BTN_PORT,BTN_PIN));
	}
}

