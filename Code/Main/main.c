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
#include "OBJ_MODEL.h"

BaseType_t Init_(void);

BaseType_t Init_()
{
	BaseType_t TaskCreation = pdFALSE;
	Core_Init();
	
	if(Get_IO_State())		/*if peripheral init correctly*/
	{
		/*inverse state (for board revision 1 and 2)*/
		IO_Pointer->INPUTS = ~IO_Pointer->INPUTS;
		SYNC_LED_OFF;
		Set_IO_Byte(0x00);
		
		InputEvent = xSemaphoreCreateCounting(3,0);
		xMutex_BUS_BUSY = xSemaphoreCreateMutex();
		
		/*start obj model*/
		OBJ_task_init(&OBJ_MODEL_MEM_ALLOCATION,tick_50ms);
		
		/*run with higher priority (use I2C)*/
		TaskCreation = xTaskCreate(vGetIOState,"I/O pool ", system_stack, NULL,system_prior, NULL );
		/*PID regulator*/
		TaskCreation &= xTaskCreate(vTask_regulator,"PID", user_stack, NULL,user_prior, NULL );
		/*led driver*/
		TaskCreation &= xTaskCreate(vTask_led_driver,"led", configMINIMAL_STACK_SIZE, NULL,user_prior, NULL );
		
		if(TaskCreation == pdTRUE)
		{
			return pdTRUE;
		}
		else
		{
			SYNC_LED_ON;
			FAULT_LED_ON;
			return pdFALSE;
		}
	}
	else
	{
		SYNC_LED_ON;
		FAULT_LED_ON;	
		return pdFALSE;
	}
}
/*************************************************
					Main program 
*************************************************/
int main(void){
	
	BaseType_t __AllOk;
	__AllOk = Init_();
	if(__AllOk == pdTRUE)
	{
		vTaskStartScheduler();			/*run RTOS*/
	}
	else
	{
		while(1);
		/*waiting for watchdog reset*/
	}
}













