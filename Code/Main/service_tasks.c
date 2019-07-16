/*************************************************
* File Name          : service_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.1
* Description        : ---
**************************************************/
#include "service_tasks.h"
#include <stm32f10x.h>

/*----------- global variables-------------------*/
/*semaphore for I/O pool*/
xSemaphoreHandle InputEvent;
/*----------- local variables--------------------*/
uint32_t BlinkFrequency; //LED flashing frequency

/*mutex for I2C , perform correct transmit */
xSemaphoreHandle xMutex_BUS_BUSY;

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
