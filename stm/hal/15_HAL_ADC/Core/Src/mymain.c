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

ADC_HandleTypeDef hadc = {
		.Instance = ADC1,
		.Init = {
				.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1,
				.Resolution = ADC_RESOLUTION_12B,
				.DataAlign	= ADC_DATAALIGN_RIGHT,
				.NbrOfConversion = 1,
				.ExternalTrigConv = ADC_SOFTWARE_START,
				.Overrun = ADC_OVR_DATA_OVERWRITTEN,
		},
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

void adc_init(){
	GPIO_InitTypeDef adc= {
				.Pin = ADC_PIN,
				.Mode = GPIO_MODE_ANALOG,
	};
	ADC_ChannelConfTypeDef chan = {
			.Channel = ADC_CHANNEL_5,
			.Rank = ADC_REGULAR_RANK_1,
			.SamplingTime = ADC_SAMPLETIME_47CYCLES_5,
			.SingleDiff = ADC_SINGLE_ENDED,
	};
	__HAL_RCC_ADC_CLK_ENABLE();
	HAL_GPIO_Init(ADC_PORT, &adc);
	HAL_ADC_Init(&hadc);
	HAL_ADC_ConfigChannel(&hadc,&chan);
	HAL_ADC_Start(&hadc);
}


void my_main(void){
	initialise_monitor_handles();
	HAL_Init();
	uart_init();
	adc_init();
	while(1){
		HAL_ADC_Start(&hadc);
		HAL_ADC_PollForConversion(&hadc, 10);     // timeout = 10ms
		uint32_t val = HAL_ADC_GetValue(&hadc);
		HAL_ADC_Stop(&hadc);
		printf("%u\r\n",(unsigned int)val);
		HAL_Delay(READDELAY);
	}
}



