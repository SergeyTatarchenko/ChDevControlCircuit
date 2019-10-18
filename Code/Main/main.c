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
		
		SYNC_LED_OFF;
		Set_IO_Byte(0x00);
		InputEvent = xSemaphoreCreateCounting(3,0);
	
		FilterReady = xSemaphoreCreateBinary();
		xMutex_BUS_BUSY = xSemaphoreCreateMutex();
		xMutex_CAN_BUSY = xSemaphoreCreateMutex();
		/*run with higher priority (use I2C)*/
		xTaskCreate(vGetIOState,"I/O pool ", system_stack, NULL,system_prior, NULL );
		
		/*start obj model*/
		OBJ_task_init(&task_priority,tick_50ms);
		/*PID regulator*/
		xTaskCreate(vTask_regulator,"PID", user_stack, NULL,user_prior, NULL );
		/*filter function*/
		//xTaskCreate(vTask_ADC_filter,"filter",system_stack, NULL,system_prior, NULL );
	
	}else{
		SYNC_LED_ON;
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













