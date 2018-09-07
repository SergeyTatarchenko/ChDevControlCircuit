/*************************************************
* File Name          : user_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : all code here
*************************************************/
#include "user_tasks.h"
/*************************************************
 Initial configuration and start other tasks
*************************************************/
void StartInit(void *pvParameters){	
	Core_Init();
	/*start other tasks*/
	
	/*start diagnostic of charging device*/
	xTaskCreate(vTestHardvare,"diagnostic", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	
	/*test blink*/
	xTaskCreate(vBlinker, "blink", configMINIMAL_STACK_SIZE, NULL, 3, NULL );
	
	LED_OFF;
	vTaskDelete(NULL); /*delete task*/
	
}

/*************************************************
blink via I2C
*************************************************/
void vBlinker (void *pvParameters){
	Set_IO_State(OUT7,1);
	
	for(;;){	
		Set_IO_State(OUT0,1);
		vTaskDelay(500);			
		
		Set_IO_State(OUT0,0);
		vTaskDelay(500);			
	}
}

/*************************************************
 diagnostic of hardware state (external ADC,
 check input and output state of MCP23017 )
*************************************************/
void vTestHardvare(void *pvParameters){
	
	if(Get_IO_State()){
		/*if state is received successfully (no internal circuit errors)*/
		
		
	}else{
		/*internal errors*/
	}
	
	
	for(;;){
		vTaskDelay(500);
	}
//	vTaskDelete(NULL); /*delete task*/
	
}

