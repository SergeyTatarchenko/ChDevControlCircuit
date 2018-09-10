/*************************************************
* File Name          : user_tasks.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : user_tasks.c header
*************************************************/
#include "stm32f10x.h"
#include "i2c.h"
#include "adc.h"
#include "dma.h"
#include "pwm.h"
#include "usart.h"
#include "mcp23x17.h"
#include "global.h"
/*----------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/*-----------local define-----------------------*/

/*-----------local function prototypes----------*/

/*-----------global function prototypes---------*/
/*initial task*/
void StartInit(void *pvParameters);
/*internal diagnostic task*/
void vTestHardvare (void *pvParameters);
/*LED flasher with frequency parameter*/
void vBlinker (void *pvParameters);
