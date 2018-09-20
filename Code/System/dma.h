/*************************************************
* File Name          : dma.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : dma.c header
*************************************************/
#ifndef DMA_H
#define DMA_H

#include "stm32f10x.h"
#include "global.h"

/*-----------local define-----------------------*/
/**/
#define ADC1_DR_ADDR	((uint32_t)(ADC1_BASE + 0x4C))
#define ADC1_BUF_SIZE	6

/*size of transmitted message */
#define USART1_BUF_SIZE	MESSAGE_BUF_SIZE

#define USART1_DR_ADDR	((uint32_t)(USART1_BASE + 0x04))
#define DMA1_USART_ON	(DMA1_Channel4->CCR |= DMA_CCR1_EN)
#define DMA1_USART_OFF	(DMA1_Channel4->CCR &= ~DMA_CCR1_EN)
/*-----------global function prototypes---------*/
extern void DMA_ADC1_Setup(void);
extern void DMA_USART1_Setup(void);
extern void DMA_Ch4_Reload(void);
/*-----------global variables-------------------*/
extern uint16_t ADC1_DataArray[ADC1_BUF_SIZE];	
extern uint8_t	USART1_DataArray[USART1_BUF_SIZE];
#endif
