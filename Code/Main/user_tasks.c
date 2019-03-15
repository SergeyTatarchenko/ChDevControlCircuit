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
	
	for(;;){
		xQueueReceive(usart_receive_buffer,&rx_buffer,portMAX_DELAY);
		Rx_OBJ_Data(&rx_buffer);
		
		//uxQueueMessagesWaiting(usart_receive_buffer);	
		vTaskDelay(1);
	}
}



/*************************************************
1000 ms timer
*************************************************/	

void vTask_1000ms(void *pvParameters){	
		
	for(;;){
		vTaskDelay(1000);
		/*test obj upd*/
		
		this_obj(IND_obj_IO)->obj_event = 1;
		OBJ_Upd(this_obj(IND_obj_IO));
		
	}
}
