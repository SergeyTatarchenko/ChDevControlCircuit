/*************************************************
* File Name          : service_tasks.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : service_tasks.c header
*************************************************/
#ifndef SERVICE_TASKS_H
#define SERVICE_TASKS_H
#include "stm32f10x.h"

#include "global.h"
#include "user_tasks.h"
/*----------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/*----------------------------------------------*/
#include "OBJ_MODEL.h"
/*-----------local define-----------------------*/

/*-----------local function prototypes----------*/
/*-----------global variables-------------------*/
extern xSemaphoreHandle InputEvent;
extern xSemaphoreHandle xMutex_BUS_BUSY;
/*-----------global function prototypes---------*/
/*LED flasher with frequency parameter*/
void vBlinker (void *pvParameters);
/* the task of reading the state of the I/O ports */
void vGetIOState(void *pvParameters);

void vTask_main(void *pvParameters);
void vTask_Handler_Data(void *pvParameters);
void vTask_Transfer_Data(void *pvParameters);

/*----------------------------------------------*/
#define system_prior		(configMAX_PRIORITIES-1)
#define usart_rx_prior		(configMAX_PRIORITIES-2)
#define usart_tx_prior		(configMAX_PRIORITIES-3)
#define board_prior			(configMAX_PRIORITIES-4)
/*----------------------------------------------*/
#define user_stack		(unsigned short) 256
#define usart_stack		(unsigned short) 256
#define led_stack		(unsigned short) 32
#define system_stack	(unsigned short) 128
/*----------------------------------------------*/
#endif


