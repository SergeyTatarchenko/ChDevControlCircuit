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
	xTaskCreate(StartInit, "Program start", configMINIMAL_STACK_SIZE, NULL, 5, NULL );
	
	/*run RTOS*/
	vTaskStartScheduler();
	
	/*add handler for stack overflow */
	while(1);
	
}













