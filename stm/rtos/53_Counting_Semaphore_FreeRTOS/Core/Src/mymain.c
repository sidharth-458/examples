/*
 * mymain.c
 *
 *  Created on: Nov 21, 2025
 *      Author: sid
 */
#include<FreeRTOS.h>
#include<task.h>
#include<semphr.h>
#include<system_stm32l4xx.h>
#include<stdio.h>
#include<errno.h>
#include"main.h"
#include<queue.h>
SemaphoreHandle_t mutex;
void high(void * pv){
	while(1){
		vTaskDelay(pdMS_TO_TICKS(1000));
		xSemaphoreTake(mutex,portMAX_DELAY);
		printf("high\n");
		xSemaphoreGive(mutex);
	}
}

void med(void * pv){
	printf("medium");
	while(1){
		__NOP();
	}
}

void low(void *pv){
	while(1){
		xSemaphoreTake(mutex,portMAX_DELAY);
		printf("taking one in a pool\n");
		vTaskDelay(pdMS_TO_TICKS(100));
		xSemaphoreGive(mutex);
		vTaskDelay(pdMS_TO_TICKS(10000));
	}
}
extern void initialise_monitor_handles();
void my_main(void){
	BaseType_t err;
	initialise_monitor_handles();
	mutex = xSemaphoreCreateCounting(2,2);
	err = xTaskCreate(high,"hgih",configMINIMAL_STACK_SIZE,NULL,6,NULL);
	if(err == pdFAIL)
		goto damn;
	err = xTaskCreate(low,"low1",configMINIMAL_STACK_SIZE,NULL,0,NULL);
	if(err == pdFAIL)
		goto damn;
	err = xTaskCreate(low,"low2",configMINIMAL_STACK_SIZE,NULL,0,NULL);
	if(err == pdFAIL)
		goto damn;
	err = xTaskCreate(low,"low3",configMINIMAL_STACK_SIZE,NULL,0,NULL);
	if(err == pdFAIL)
		goto damn;
	vTaskStartScheduler();
damn:
	errno = EINVAL;
	perror("task create fail");

	for(;;);
}
