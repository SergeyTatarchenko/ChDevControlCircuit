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

	/*start other tasks*/	
	//state = Get_IO_State();
	state =1;
	
	/*high level tasks*/
	if(state){
		LED_OFF;
		/*run with higher priority (use I2C)*/
		xTaskCreate(vGetIOState,"I/O pool ", system_stack, NULL,system_prior, NULL );
		/*main thread*/
		xTaskCreate(vTask_main,"main thread",user_stack, NULL, board_prior, NULL );	
		/* RX Handler */
		xTaskCreate(vTask_Handler_Data,"Handler",usart_stack, NULL,usart_prior, NULL );
		
		
		/*start obj model*/
		OBJ_Init();
	
	
	}else{
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

volatile uint8_t power_on;

/*************************************************
USART RX handler 
*************************************************/
void vTask_Handler_Data(void *pvParameters){
	USART_FRAME rx_buffer;
	
	/*USART receive complete interrupt on NVIC*/
	NVIC_EnableIRQ (USART1_IRQn);
	for(;;){
		xQueueReceive(usart_receive_buffer,&rx_buffer,portMAX_DELAY);
		Rx_OBJ_Data(&rx_buffer);
		
		//uxQueueMessagesWaiting(usart_receive_buffer);	
		vTaskDelay(1);
	}
}
/*************************************************
				main tread
*************************************************/	

void vTask_main(void *pvParameters){
	
	board_state.bit.mode = USART_MODE;
	board_state.bit.hwobj = TRUE;
	board_state.bit.debug = TRUE;
	
	for(;;){
		vTaskDelay(1);		
		if(board_state.bit.power == 1){
			board_task();		
		}
	}
}

