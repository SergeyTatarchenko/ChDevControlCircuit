/*************************************************
* File Name          : service_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : ---
**************************************************/
#include "service_tasks.h"
/*----------- global variables-------------------*/
/*semaphore for I/O pool*/
xSemaphoreHandle InputEvent;
/*----------- local variables--------------------*/
uint32_t BlinkFrequency; //LED flashing frequency

/*mutex for I2C , perform correct transmit */
xSemaphoreHandle xMutex_BUS_BUSY;

/*************************************************
 Initial configuration and start other tasks
*************************************************/
void StartInit(void *pvParameters){	
	_Bool state;
	Core_Init();
	LED_ON;
	/**/
	InputEvent = xSemaphoreCreateCounting(3,0);
	xMutex_BUS_BUSY = xSemaphoreCreateMutex();
	//
	state = Get_IO_State();
	
	/*start other tasks*/
	
	/*high level tasks*/
	if(state){
		
		
		/*run with higher priority (use I2C)*/
		xTaskCreate(vGetIOState,"I/O pool ", configMINIMAL_STACK_SIZE, NULL, 5, NULL );
		/************************************/
		
		/*program timers*/
		xTaskCreate(vTask_1000ms,"1000 ms pool",configMINIMAL_STACK_SIZE, NULL, 3, NULL );	
		
		/*create test blinker */
		BlinkFrequency = 500;
		xTaskCreate(vBlinker,"blink",configMINIMAL_STACK_SIZE, (void*)&BlinkFrequency, 2, NULL );	
		
		
		
	}
	else{
		
		LED_ON;
		/*internal error, loading aborted*/		
		// add error handler
	}
	vTaskDelete(NULL); /*delete task*/	
}
/*************************************************
the task is performed on a semaphore "InputEvent"
*************************************************/
void vGetIOState(void *pvParameters){
	UBaseType_t SemaphoreCount;
	for(;;){
		/*the task is waiting for the semaphore */
		xSemaphoreTake(InputEvent,portMAX_DELAY);
		/*task take the semaphore */
		
		xSemaphoreTake(xMutex_BUS_BUSY,portMAX_DELAY);
		/*get current IO state*/
		if(!Get_IO_State()){
			// internal circuit error (add handler)
		}
		xSemaphoreGive(xMutex_BUS_BUSY);
			
		SemaphoreCount = uxSemaphoreGetCount(InputEvent);	
		if(SemaphoreCount > 1){
			//error overclocking IO port(add handler)
		}
	}
//	vTaskDelete(NULL);
}

/*************************************************
LED blink (get blink frequency in ms
as task parameter)
*************************************************/
void vBlinker (void *pvParameters){
	
	volatile TickType_t *BlinkFreq;
	BlinkFreq =(TickType_t*)pvParameters;
	
	for(;;){	
		LED_ON;
		vTaskDelay((*BlinkFreq)/4);			
		LED_OFF;
		vTaskDelay(3*(*BlinkFreq)/4);
		vTaskDelay(*BlinkFreq);			
	}
}
