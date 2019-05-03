/*************************************************
* File Name          : main.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : main file
*************************************************/
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
	CAN_init();
	xTaskCreate(StartInit, "Program start", configMINIMAL_STACK_SIZE, NULL, 5, NULL );
	
	
	vTaskStartScheduler();
	/*add handler for stack overflow */
	while(1);
	
}













