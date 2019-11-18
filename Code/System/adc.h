/*************************************************
* File Name          : adc.h
* Author             : Tatarchenko S.
* Version            : v 1.1
* Description        : adc.c header
*************************************************/
#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"
/*-----------local define-----------------------*/
#define ADC1_TimeOut	500
#define ADC1_On		(ADC1->CR2 |= ADC_CR2_SWSTART);
#define ADC1_Off	(ADC1->CR2 &= ~ADC_CR2_SWSTART);

#define ADC_DEPTH		4096
#define INT_ADC_REF		3300	/*mV*/


#define num_of_adc_conversion	9
/*-----------global function prototypes---------*/
extern void ADC_Init(void);
/*-----------local function prototypes----------*/

#endif
