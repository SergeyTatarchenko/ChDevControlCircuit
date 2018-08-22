/*************************************************
* File Name          : dma.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : DMA configuration
*************************************************/
#include "dma.h"
/*-----------global variables-------------------*/
uint16_t ADC1_DataArray[ADC1_BUF_SIZE];	
/*************************************************
Init DMA Channel for ADC1  
*************************************************/
void DMA_ADC1_Setup(){
	/*DMA1 clock*/
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	/*memory increment mode enabled,
	memory\peripheral size size 16 bit
	circular mode					*/
	DMA1_Channel1->CCR |= DMA_CCR1_MINC|DMA_CCR1_PSIZE_0|
						  DMA_CCR1_PSIZE_0|DMA_CCR1_CIRC;
	/*peripheral address*/
	DMA1_Channel1->CPAR |= ADC1_DR_ADDR;
	/*pointer to memory address*/
	DMA1_Channel1->CMAR |= (uint32_t)ADC1_DataArray;
	/*number of data to transfer*/
	DMA1_Channel1->CNDTR = ADC1_BUF_SIZE;
	/*high priority level */
	DMA1_Channel1->CCR |= DMA_CCR1_PL_1;
	/*DMA1 on*/
	DMA1_Channel1->CCR |= DMA_CCR1_EN;
}
