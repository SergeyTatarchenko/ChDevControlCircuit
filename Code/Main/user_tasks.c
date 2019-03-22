/*************************************************
* File Name          : user_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : all code here
**************************************************/
#include "user_tasks.h"
/*************************************************/
/*************************************************
USART RX handler 
*************************************************/
void vTask_Handler_Data(void *pvParameters){
	TX_RX_FRAME rx_buffer;
	
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

void vTask_1000ms(void *pvParameters){		
	for(;;){
		vTaskDelay(10);
		/*test obj upd*/
		adc_calc_value();
		Upd_All_OBJ();
		OBJ_Event(IND_obj_TICK);
		OBJ_Event(IND_obj_ADC1);
	}
}
