/*************************************************
* File Name          : adc.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : adc.c header
*************************************************/
#include "stm32f10x.h"
/*-----------local define-----------------------*/
#define ADC1_TimeOut	500
#define ADC1_On		(ADC1->CR2 |= ADC_CR2_SWSTART);
#define ADC1_Off	(ADC1->CR2 &= ~ADC_CR2_SWSTART);
/*-----------global function prototypes---------*/
extern void ADC_Init(void);
/*-----------local function prototypes----------*/
