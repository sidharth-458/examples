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
int fast = 0;
#define	LEDFAST (1<<1)
#define LEDSLOW	(1<<0)
void LEDTask(void * pv){
	int delay = 1000;
	int led = 1;
	for(;;){
		uint32_t notif = 0;
		if(xTaskNotifyWait( 0,LEDSLOW | LEDFAST,&notif,0) == pdTRUE){
			if( notif & LEDSLOW)
				delay = 1000;
			else if(notif & LEDFAST)
				delay = 100;
		}
		led ^= 1;
		HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,led);
		vTaskDelay(pdMS_TO_TICKS(delay));
	}

}
void BTNTask(void * pv){
	int command;
	for(;;){
		int bit;
		command = HAL_GPIO_ReadPin(B1_GPIO_Port,B1_Pin);
		if(command)
			continue;
		vTaskDelay(pdMS_TO_TICKS(300));
		if( ! HAL_GPIO_ReadPin(B1_GPIO_Port,B1_Pin) ){
			/*long press*/
			bit = LEDFAST;
		}
		else{
			bit = LEDSLOW;
		}
		xTaskNotify(t1,bit,eSetBits);
		while(! HAL_GPIO_ReadPin(B1_GPIO_Port,B1_Pin) );
		vTaskDelay(pdMS_TO_TICKS(300));
	}
}
extern void initialise_monitor_handles(void);
void my_main(void){
	BaseType_t err;
	initialise_monitor_handles();
	err = xTaskCreate(LEDTask,"led",configMINIMAL_STACK_SIZE,NULL,0,&t1);
	if(err == pdFAIL){
		errno = EINVAL;
		perror("task create fail");
		for(;;);
	}
	err = xTaskCreate(BTNTask,"btn",configMINIMAL_STACK_SIZE,NULL,0,&t2);
	if(err == pdFAIL){
		errno = EINVAL;
		perror("task create fail");
		for(;;);
	}
	vTaskStartScheduler();
	for(;;);
}
