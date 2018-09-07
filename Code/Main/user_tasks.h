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
#define LED_OFF (GPIOC->BSRR = GPIO_BSRR_BS13);
#define LED_ON 	(GPIOC->BSRR = GPIO_BSRR_BR13);
/*-----------local function prototypes----------*/
void LedInit(void);
/*-----------global function prototypes---------*/

void StartInit(void *pvParameters);
void vTestHardvare (void *pvParameters);
void vBlinker (void *pvParameters);
