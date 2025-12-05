/*
 * mymain.c
 *
 *  Created on: Nov 20, 2025
 *      Author: sid
 */

#include<stm32l4xx_hal.h>

#define RX_PIN GPIO_PIN_5
#define TX_PIN GPIO_PIN_5
#define UART_PORT GPIOA

#define MSG "hello from stm32\r\n"
#define MSGDELAY 1000
UART_HandleTypeDef huart = {
	.Instance = USART2,
	.Init = {
			.BaudRate = 115200,
			.WordLength = UART_WORDLENGTH_8B,
			.StopBits = UART_STOPBITS_1,
			.Parity = UART_PARITY_NONE,
			.Mode = UART_MODE_TX_RX,
			.HwFlowCtl = UART_HWCONTROL_NONE,
			.OverSampling = UART_OVERSAMPLING_16,

	}
};


void uart_init(){

	GPIO_InitTypeDef uart= {
			.Pin = TX_PIN | RX_PIN,
			.Mode = GPIO_MODE_AF_PP,
			.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
	};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
	HAL_GPIO_Init(UART_PORT, &uart);
	HAL_UART_Init(&huart);


}

void my_main(void){
	HAL_Init();
	uart_init();
	while(1){
		HAL_UART_Transmit(&huart,(uint8_t *)MSG,18,20);
		HAL_Delay(MSGDELAY);
	}
}



