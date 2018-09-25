/*************************************************
* File Name          : service_tasks.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : service_tasks.c header
*************************************************/
#ifndef SERVICE_TASKS_H
#define SERVICE_TASKS_H

#include "global.h"
/*----------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/*-----------local define-----------------------*/

/*-----------local function prototypes----------*/
/*-----------global variables-------------------*/
extern xSemaphoreHandle InputEvent;
/*-----------global function prototypes---------*/
/*initial task*/
void StartInit(void *pvParameters);
/*internal diagnostic task*/
void vTestHardvare (void *pvParameters);
/*LED flasher with frequency parameter*/
void vBlinker (void *pvParameters);
/* the task of reading the state of the I/O ports */
void vGetIOState(void *pvParameters);

/* the task for error handling */
void vInternalErrorHandler(void *pvParameters);

#endif


