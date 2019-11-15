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
#include "RTOS.h"
/*----------------------------------------------*/
#include "PID.h"

/*-----------local define-----------------------*/
/*-----------local function prototypes----------*/
/*-----------global variables-------------------*/
/*-----------global function prototypes---------*/
void board_task(int task_tick);
void board_pr_init(void);

extern xSemaphoreHandle FilterReady;

void vTask_ADC_filter(void *pvParameters);
void vTask_regulator(void *pvParameters);
void vTask_led_driver(void *pvParameters);

void filter_enable(void);

uint16_t pd_regulator(uint16_t set_value,uint16_t feedback,uint16_t gisteresis); 

#endif
