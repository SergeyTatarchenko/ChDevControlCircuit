/*************************************************
* File Name          : ext.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : ext.c header
*************************************************/
#ifndef EXT_H
#define EXT_H

#include "stm32f10x.h"
/*-----------local define-----------------------*/
#define EXTI_ENABLE 	(EXTI->IMR |= EXTI_IMR_MR6|EXTI_IMR_MR7)
#define EXTI_DISABLE 	(EXTI->IMR &= ~(EXTI_IMR_MR6|EXTI_IMR_MR7))
/*-----------global function prototypes---------*/
extern void EXTI_Init(void);
extern void NVIC_Init(void);
/*-----------local function prototypes----------*/


#endif
