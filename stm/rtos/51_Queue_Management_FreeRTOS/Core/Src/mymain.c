/*
 * mymain.c
 *
 *  Created on: Nov 21, 2025
 *      Author: sid
 */
#include<FreeRTOS.h>
#include<task.h>
//#include<semphr.h>
#include<queue.h>
#include<system_stm32l4xx.h>
#include<stdio.h>
#include<errno.h>
#include"main.h"
QueueHandle_t qu;
void send(void * pv){
	char buff[] = "hello";
	int i = 0;
	while(1){
		if(xQueueSend(qu,&buff[i++%5],portMAX_DELAY)){
			printf("sent character\n");
		}
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}


void recv(void *pv){
	char buff;
	while(1){
		if(xQueueReceive(qu,&buff,portMAX_DELAY)){
			printf("%c received from send\n",buff);
		}
	}
}
extern void initialise_monitor_handles();
void my_main(void){
	BaseType_t err;
	initialise_monitor_handles();
	qu = xQueueCreate(10,1);
	err = xTaskCreate(send,"send",configMINIMAL_STACK_SIZE,NULL,6,NULL);
	if(err == pdFAIL){
		errno = EINVAL;
		perror("task create fail");
	}
	err = xTaskCreate(recv,"recv",configMINIMAL_STACK_SIZE,NULL,0,NULL);
	if(err == pdFAIL){
		errno = EINVAL;
		perror("task create fail");
	}
	vTaskStartScheduler();
	for(;;);
}
