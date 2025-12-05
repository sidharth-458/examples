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
		printf("low task takes mutex\n");
		xTaskCreate(med,"med",configMINIMAL_STACK_SIZE,NULL,3,NULL);
		taskYIELD();
		xSemaphoreGive(mutex);
		vTaskDelay(pdMS_TO_TICKS(10000));
	}
}
extern void initialise_monitor_handles();
void my_main(void){
	BaseType_t err;
	initialise_monitor_handles();
	mutex = xSemaphoreCreateMutex();
	err = xTaskCreate(high,"hgih",configMINIMAL_STACK_SIZE,NULL,6,NULL);
	if(err == pdFAIL){
		errno = EINVAL;
		perror("task create fail");
	}
	err = xTaskCreate(low,"low",configMINIMAL_STACK_SIZE,NULL,0,NULL);
	if(err == pdFAIL){
		errno = EINVAL;
		perror("task create fail");
	}
	vTaskStartScheduler();
	for(;;);
}
