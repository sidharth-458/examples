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

//40 counts in usec
static int tog = 0;
TIM_HandleTypeDef timer = {
		.Instance = TIM3,
		.Init = {
				.Prescaler = 1600 -1,
				.Period = 1000 - 1,
				.CounterMode = TIM_COUNTERMODE_UP,
				.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE,
		},
};
static void tim_init(){

	__HAL_RCC_TIM3_CLK_ENABLE();
	HAL_TIM_Base_Init(&timer);
	HAL_NVIC_SetPriority(TIM3_IRQn,0,0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
	HAL_TIM_Base_Start_IT(&timer);
}
void TIM3_IRQHandler(void){
	HAL_TIM_IRQHandler(&timer);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * h){
	HAL_GPIO_WritePin(LED_PORT,LED_PIN,(tog++)%2);
}
static void led_init(){
	GPIO_InitTypeDef led = {
			.Pin = LED_PIN,
			.Mode = GPIO_MODE_OUTPUT_PP,
	};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(LED_PORT, &led);
}

void my_main(void){

	HAL_Init();
	led_init();
	tim_init();
	while(1){
	}
}

