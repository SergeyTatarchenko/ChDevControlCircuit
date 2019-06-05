/*************************************************
* File Name          : main.c
* Author             : Tatarchenko S.
* Version            : v 1.1
* Description        : main file
*************************************************/
/*----------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/*----------------------------------------------*/
#include "service_tasks.h"

void Init_(void);

void Init_(){
	Core_Init();	
	if(Get_IO_State()){
		
		LED_OFF;
		Set_IO_Byte(0x00);
		InputEvent = xSemaphoreCreateCounting(3,0);
		xMutex_BUS_BUSY = xSemaphoreCreateMutex();
		/*create mutex for correct usart transmit*/
		xMutex_USART_BUSY = xSemaphoreCreateMutex();
		usart_receive_buffer = xQueueCreate(MES_BUF_SIZE,sizeof(USART_FRAME));

		/*run with higher priority (use I2C)*/
		xTaskCreate(vGetIOState,"I/O pool ", system_stack, NULL,system_prior, NULL );
		/*main thread*/
		xTaskCreate(vTask_main,"main thread",user_stack, NULL, board_prior, NULL );	
		/* RX Handler */
		xTaskCreate(vTask_Handler_Data,"Handler",usart_stack, NULL,usart_rx_prior, NULL );
		/* RX Handler */
		xTaskCreate(vTask_Transfer_Data,"TX",usart_stack, NULL,usart_tx_prior, NULL );
		
		/*start obj model*/
		OBJ_Init();
	}else{
		LED_ON;
	}
}
/*************************************************
					Main program 
*************************************************/
int main(void){
	Init_();
	
	/*run RTOS*/
	vTaskStartScheduler();
	/*add handler for stack overflow */	
}













