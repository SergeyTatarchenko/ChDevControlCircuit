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
		adc_calc_value();
		
		send_usart_message(buff,(uint32_t)USART1_DEFAULT_BUF_SIZE);
		vTaskDelay(1000);
	}
}
