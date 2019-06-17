/*************************************************
* File Name          : service_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
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
            USART TX thread 
*************************************************/
void vTask_Transfer_Data(void *pvParameters){
	
	for(;;){
		if(board_state.bit.power == 1){
			FAST_Upd_All_OBJ_USART();
		}
	vTaskDelay(10);
	}
}
/*************************************************
				main tread
*************************************************/	

void vTask_main(void *pvParameters){
	
	volatile int tick = 0,overload = 3600000UL;
	board_state.bit.mode = USART_MODE;
	board_state.bit.hwobj = HARDWARE_OBJECT;
	board_state.bit.debug = DEBUG_MODE;
	board_pr_init();
	
	for(;;){
		vTaskDelay(1);
		IWDG_RELOAD;		
		/*while bit power on (bit state on in obj_STATUS))*/
		if(board_state.bit.power == 1){
			board_task(tick);
			if(tick<=overload ){
				tick++;
			}
			else{
				tick = 0;
			}
		}
	}
}

