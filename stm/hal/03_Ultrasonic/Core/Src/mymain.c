/*
 * mymain.c
 *
 *  Created on: Nov 20, 2025
 *      Author: sid
 */


#include<stm32l4xx_hal.h>

#define PING_PIN GPIO_PIN_13
#define PING_PORT GPIOC
#define RECV_PIN GPIO_PIN_12
#define RECV_PORT GPIOC
static void ping_init(){
	GPIO_InitTypeDef ping = {
			.Pin = PING_PIN,
			.Mode = GPIO_MODE_OUTPUT_PP,
	};
	__HAL_RCC_GPIOC_CLK_ENABLE();
	HAL_GPIO_Init(PING_PORT, &ping);
}
static void recv_init(){
	GPIO_InitTypeDef recv = {
			.Pin = RECV__PIN,
			.Mode = GPIO_MODE_INPUT,
	};
	__HAL_RCC_GPIOC_CLK_ENABLE();
	HAL_GPIO_Init(RECV_PORT, &recv);
}
void my_main(void){
	GPIO_PinState state;
	HAL_Init();
	HAL_Timer1
	recv_init();
	ping_init();
	while(1){
		state = HAL_GPIO_WritePin(PING_PORT,PING_PIN);
		delay(10);
	}
}

