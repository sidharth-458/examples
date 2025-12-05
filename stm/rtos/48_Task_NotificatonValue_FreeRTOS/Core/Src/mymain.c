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
//extern void initialise_monitor_handles();
int led = 0;
#define LEDBYE (1<<15)
void LEDTask(void * pv){
	for(;;){
		uint32_t notif = 0;
		if(xTaskNotifyWait( 0,0,&notif,0) == pdTRUE){
			if( notif & LEDBYE)
				goto CLEANUP;
		}

		HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,led);
		vTaskDelay(pdMS_TO_TICKS(1));
	}
CLEANUP:
	HAL_GPIO_DeInit(LD2_GPIO_Port,LD2_Pin);
	vTaskDelete(NULL);

}
void BTNTask(void * pv){
	int togcount= 0;
	int command;
	for(;;){
		command = HAL_GPIO_ReadPin(B1_GPIO_Port,B1_Pin);
		if(command == 0){
			led ^=1;
			vTaskDelay(pdMS_TO_TICKS(100));
			togcount++;
		}
		if(togcount == 10){
					xTaskNotify(t1,LEDBYE,eSetBits);
		}
		vTaskDelay(pdMS_TO_TICKS(1));

	}
}
void my_main(void){
	BaseType_t err;
//	initialise_monitor_handles();
	err = xTaskCreate(LEDTask,"led",configMINIMAL_STACK_SIZE,NULL,0,&t1);
	if(err == pdFAIL){
		errno = EINVAL;
		perror("task create fail");
	}
	err = xTaskCreate(BTNTask,"btn",configMINIMAL_STACK_SIZE,NULL,0,&t2);
	if(err == pdFAIL){
		errno = EINVAL;
		perror("task create fail");
	}
	vTaskStartScheduler();
	for(;;);
}
