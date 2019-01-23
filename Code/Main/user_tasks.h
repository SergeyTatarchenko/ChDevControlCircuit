/*************************************************
* File Name          : user_tasks.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : user_tasks.c header
*************************************************/
#ifndef USER_TASKS_H
#define USER_TASKS_H

#include "global.h"
/*----------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/*-----------local define-----------------------*/
/*-----------local function prototypes----------*/
void send_usart_message(uint8_t *arr,uint32_t buf_size);
/*-----------global variables-------------------*/
/*-----------global function prototypes---------*/
extern void vTask_1000ms(void *pvParameters);

#endif
