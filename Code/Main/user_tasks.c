/*************************************************
* File Name          : user_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : all code here
**************************************************/
#include "user_tasks.h"
/*************************************************/
/*----------- global variables-------------------*/
/*----------- local variables--------------------*/
uint32_t BlinkFrequency; //LED flashing frequency

/*semaphore for I/O pool*/
xSemaphoreHandle InputEvent;
/*mutex for I2C bus , perform correct transmit */
xSemaphoreHandle xMutex_BUS_BUSY;

/*************************************************
 Initial configuration and start other tasks
*************************************************/
void StartInit(void *pvParameters){	
	_Bool state;
	Core_Init();
	
	
	/**/
	InputEvent = xSemaphoreCreateCounting(3,0);
	xMutex_BUS_BUSY = xSemaphoreCreateMutex();
	//
	state = Get_IO_State();
	
	/*start other tasks*/
	
	/*high level tasks*/
	if(state){
		/*run with higher priority (use I2C)*/
		xTaskCreate(vGetIOState,"I/O pool ", configMINIMAL_STACK_SIZE, NULL, 6, NULL );	
	
		/*user level tasks*/
	
		/*start diagnostic of charging device*/
		xTaskCreate(vTestHardvare,"diagnostic", configMINIMAL_STACK_SIZE, NULL, 3, NULL );
	
		vTaskDelete(NULL); /*delete task*/		
	}else{
		/*internal error, loading aborted*/
		LED_OFF;
		// add error handler
		vTaskDelete(NULL); /*delete task*/
	}
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
	//vTaskDelete(NULL);
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
		vTaskDelay(*BlinkFreq);			
		LED_OFF;
		vTaskDelay(*BlinkFreq);			
	}
}

/*************************************************
 diagnostic of hardware state (external ADC,
 check input and output state of MCP23017 )
*************************************************/
void vTestHardvare(void *pvParameters){
	
	BlinkFrequency = 250;
	/*test blink*/
	xTaskCreate(vBlinker, "blink", configMINIMAL_STACK_SIZE,(void*)&BlinkFrequency, 4, NULL );	
	
	
		
	for(;;){
		vTaskDelay(1500);
	}
//	vTaskDelete(NULL); /*delete task*/
	
}

