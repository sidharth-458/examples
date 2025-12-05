/*
 * mymain.c
 *
 *  Created on: Nov 20, 2025
 *      Author: sid
 */

#include<stm32l4xx_hal.h>
#include<stdio.h>
#include<string.h>
#define RX_PIN GPIO_PIN_5
#define TX_PIN GPIO_PIN_5
#define UART_PORT GPIOA

#define ADC_PIN GPIO_PIN_0
#define ADC_PORT GPIOA
#define READDELAY 1000
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

extern DAC_HandleTypeDef hdac1;

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
void DAC1_Init_PA4(void)
{
    /* 1) Enable clocks */
    __HAL_RCC_GPIOA_CLK_ENABLE();     // for PA4 pin
    __HAL_RCC_DAC1_CLK_ENABLE();      // for DAC peripheral

    /* 2) Configure PA4 as analog (no pull) */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin  = GPIO_PIN_4;                 // PA4
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* 3) Configure DAC peripheral */
    hdac1.Instance = DAC1;
    HAL_DAC_Init(&hdac1);

    /* 4) Configure DAC Channel 1, normal mode */
    DAC_ChannelConfTypeDef sConfig = {0};
    sConfig.DAC_Trigger      = DAC_TRIGGER_NONE;       // software trigger
    sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;

    HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1);

    /* 5) Enable DAC channel */
    HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
}
void my_main(void){
	initialise_monitor_handles();
	HAL_Init();
	uart_init();
	DAC1_Init_PA4();
	while(1){
		HAL_Delay(READDELAY);
	}
}



