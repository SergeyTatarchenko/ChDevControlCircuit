/*************************************************
* File Name          : dma.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : dma.c header
*************************************************/
#ifndef DMA_H
#define DMA_H

#include "stm32f10x.h"
/*-----------local define-----------------------*/
#define ADC1_DR_ADDR	((uint32_t)(ADC1_BASE + 0x4C))
#define ADC1_BUF_SIZE	6
/*-----------global function prototypes---------*/
extern void DMA_ADC1_Setup(void);
/*-----------global variables-------------------*/
extern uint16_t ADC1_DataArray[ADC1_BUF_SIZE];	

#endif
