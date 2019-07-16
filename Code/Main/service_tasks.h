/*************************************************
* File Name          : service_tasks.h
* Author             : Tatarchenko S.
* Version            : v 1.1
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
/*----------------------------------------------*/
#define system_prior	(configMAX_PRIORITIES-1)
/*----------------------------------------------*/
#define system_stack	(unsigned short) 128
/*----------------------------------------------*/
#endif


