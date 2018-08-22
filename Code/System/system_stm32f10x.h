/*************************************************
* File Name          : system_stm32f10x.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : system_stm32f10x.c header
*************************************************/
#include "stm32f10x.h"
/*-----------local define-----------------------*/
#define PLL_FREQ 60000000UL

#define APB1_FREQ PLL_FREQ
#define APB2_FREQ PLL_FREQ

/*-----------global function prototypes---------*/
extern void SystemInit(void);
