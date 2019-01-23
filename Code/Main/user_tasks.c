/*************************************************
* File Name          : user_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : all code here
**************************************************/
#include "user_tasks.h"
/*************************************************/


/*************************************************
1000 ms timer
*************************************************/	

void vTask_1000ms(void *pvParameters){
	/*test message*/
	uint8_t buff[USART1_DEFAULT_BUF_SIZE] = {"test message\r\n"};
	
	
	for(;;){
		
		send_usart_message(buff,(uint32_t)USART1_DEFAULT_BUF_SIZE);
		vTaskDelay(1000);
	}
}

/*************************************************
send USART message, use DMA , low priority 
*************************************************/
void send_usart_message(uint8_t *buf,uint32_t buf_size){
	
	memcpy(USART1_DataArray,buf,buf_size);
	DMA_Ch4_Reload(buf_size);
}                                                                     
