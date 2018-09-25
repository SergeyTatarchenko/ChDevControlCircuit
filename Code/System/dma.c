/*************************************************
* File Name          : dma.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : DMA configuration
*************************************************/
#include "dma.h"
/*-----------global variables-------------------*/
uint16_t ADC1_DataArray[ADC1_BUF_SIZE];
uint8_t USART1_DataArray[USART1_DEFAULT_BUF_SIZE]={"voltage\r\n"};
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
/*************************************************
Init DMA Channel for USART1 
*************************************************/
void DMA_USART1_Setup(){
	/*DMA1 clock*/
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	/*memory increment mode enabled,
	memory\peripheral size size 8 bit
	circular mode,memory to peripheral direction*/
	DMA1_Channel4->CCR |= DMA_CCR1_MINC|DMA_CCR1_DIR;
	/*peripheral address*/
	DMA1_Channel4->CPAR |= (uint32_t)&(USART1->DR);
	/*pointer to memory address*/
	DMA1_Channel4->CMAR |= (uint32_t)&USART1_DataArray[0];
	/*number of data to transfer*/
	DMA1_Channel4->CNDTR = USART1_DEFAULT_BUF_SIZE;
	/*medium priority level */
	DMA1_Channel4->CCR |= DMA_CCR1_PL_1;
}
/*************************************************
Reload DMA Channel 4 
*************************************************/
void DMA_Ch4_Reload(int new_buf_size){
	DMA1_Channel4->CCR &= ~DMA_CCR1_EN;
	DMA1_Channel4->CNDTR = new_buf_size;
	DMA1_Channel4->CCR |= DMA_CCR1_EN;
}


