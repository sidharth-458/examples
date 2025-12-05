/*
 * mymain.c
 *
 *  Created on: Nov 20, 2025
 *      Author: sid
 */


#include<stm32l4xx_hal.h>
static int tog;
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
			.Mode = GPIO_MODE_IT_FALLING,
	};
	__HAL_RCC_GPIOC_CLK_ENABLE();
	HAL_GPIO_Init(BTN_PORT, &btn);
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);        // priority (2,0) – adjust as needed
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(BTN_PIN);  // pass the pin to HAL
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == BTN_PIN)
    {
        // This runs on every PA0 rising edge
    	tog = ~tog;
        HAL_GPIO_WritePin(LED_PORT,LED_PIN,tog);
    }
}

void my_main(void){
	HAL_Init();
	led_init();
	btn_init();
	while(1){

	}
}

