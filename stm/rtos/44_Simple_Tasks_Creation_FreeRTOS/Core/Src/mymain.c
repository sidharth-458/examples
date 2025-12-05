/*
 * mymain.c
 *
 *  Created on: Nov 21, 2025
 *      Author: sid
 */
#include<FreeRTOS.h>
#include<task.h>
#include<system_stm32l4xx.h>
#include<stdio.h>
#include<errno.h>
#include"main.h"
TaskHandle_t t1;
TaskHandle_t t2;
extern void initialise_monitor_handles();
void helloTask(void * pv){
	for(;;){
		printf("hello\n");
		taskYIELD();
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
void byeTask(void * pv){
	for(;;){
		printf("bye\n");
		taskYIELD();
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
void my_main(void){
	BaseType_t err;
	initialise_monitor_handles();
	err = xTaskCreate(helloTask,"task1",configMINIMAL_STACK_SIZE,NULL,0,&t1);
	if(err == pdFAIL){
		errno = EINVAL;
		perror("task create fail");
	}
	err = xTaskCreate(byeTask,"task2",configMINIMAL_STACK_SIZE,NULL,0,&t2);
	if(err == pdFAIL){
		errno = EINVAL;
		perror("task create fail");
	}
	vTaskStartScheduler();
	for(;;);
}
