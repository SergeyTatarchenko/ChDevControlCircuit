/*************************************************
* File Name          : user_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : all code here
*************************************************/
#include "user_tasks.h"
/************************************************/
/*----------- global variables-------------------*/
/*----------- local variables--------------------*/
uint32_t BlinkFrequency; //LED flashing frequency


/*************************************************
 Initial configuration and start other tasks
*************************************************/
void StartInit(void *pvParameters){	
	Core_Init();
	/*start other tasks*/
	
	/*start diagnostic of charging device*/
	xTaskCreate(vTestHardvare,"diagnostic", configMINIMAL_STACK_SIZE, NULL, 2, NULL );

	//LED_OFF;
	vTaskDelete(NULL); /*delete task*/
	
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
	
	if(Get_IO_State()){
		/*if state is received successfully (no internal circuit errors)*/
		
		/*beginning test of correct connecting */
		BlinkFrequency = 500;
		/*test blink*/
		xTaskCreate(vBlinker, "blink", configMINIMAL_STACK_SIZE,(void*)&BlinkFrequency, 3, NULL );
		
		
	}else{
		/*internal errors*/
	}

	
	for(;;){
		vTaskDelay(1500);
	//	vTaskDelete(vBlinker);
		
	}
//	vTaskDelete(NULL); /*delete task*/
	
}

