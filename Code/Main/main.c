/*************************************************
* File Name          : main.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : main file
*************************************************/
#define HSE_10MHz
//#define HSE_8MHz
//#define HSE_12MHz

/*----------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/*----------------------------------------------*/
#include "service_tasks.h"
/*************************************************
Main program 
*************************************************/
int main(void){
	xTaskCreate(StartInit, "Program start", configMINIMAL_STACK_SIZE, NULL, 5, NULL );
	
	/*run RTOS*/
	vTaskStartScheduler();
	
	/*add handler for stack overflow */
	while(1);
	
}













