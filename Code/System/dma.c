/*************************************************
* File Name          : dma.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : DMA configuration
*************************************************/
#include "dma.h"

/*----------- global variables-------------------*/

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
						  DMA_CCR1_MSIZE_0|DMA_CCR1_CIRC;
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
	
	/*init DMA for USART1 transmit*/
	
	/*memory increment mode enabled,
	memory\peripheral size size 8 bit
	single mode,memory to peripheral direction*/
	DMA1_Channel4->CCR &= 0;
	DMA1_Channel4->CCR |= DMA_CCR1_MINC|DMA_CCR1_DIR;
	/*peripheral address*/
	DMA1_Channel4->CPAR |= (uint32_t)&(USART1->DR);
	/*pointer to memory address*/
	DMA1_Channel4->CMAR |= (uint32_t)&usart_data_transmit_array[0];
	/*number of data to transfer*/
	DMA1_Channel4->CNDTR = (uint32_t)USART1_DEFAULT_BUF_SIZE;
	/*Transfer complete interrupt enable */
	DMA1_Channel4->CCR |= DMA_CCR1_TCIE;
	
	/*medium priority level */
	DMA1_Channel4->CCR |= DMA_CCR1_PL_1;
	
	/*init DMA for USART1 receive*/
	/*memory increment mode enabled,
	memory\peripheral size size 8 bit
	single mode,peripheral to memory direction*/
	DMA1_Channel5->CCR &= 0;
	DMA1_Channel5->CCR |= DMA_CCR1_MINC;
	/*peripheral address*/
	DMA1_Channel5->CPAR |= (uint32_t)&(USART1->DR);
	/*pointer to memory address*/
	DMA1_Channel5->CMAR |= (uint32_t)&usart_data_receive_array[0];
	/*number of data to transfer*/
	DMA1_Channel5->CNDTR = (uint32_t)USART1_DEFAULT_BUF_SIZE;
	/*medium priority level */
	DMA1_Channel5->CCR |= DMA_CCR1_PL_1;
	/*Transfer complete interrupt enable */
	DMA1_Channel5->CCR |= DMA_CCR1_TCIE;
	
	/*DMA ch5 on*/
//	DMA1_Channel5->CCR |= DMA_CCR1_EN;
	
}
void DMA1_Channel4_IRQHandler(){
	
	static portBASE_TYPE xTaskWoken = pdFALSE;
	/*interrupt on transfer complete */
	if(DMA1->ISR &= DMA_ISR_TCIF4){
		DMA1->IFCR |= DMA_IFCR_CTCIF4;
	}
	/*return mutex for other tasks to usart transmit*/
	xSemaphoreGiveFromISR(xMutex_USART_BUSY,&xTaskWoken);
	
	if(xTaskWoken == pdTRUE){
		taskYIELD();
	}
	
}

void DMA1_Channel5_IRQHandler(){
	
	
		/*interrupt on transfer complete */
	if(DMA1->ISR &= DMA_ISR_TCIF5){
		DMA1->IFCR |= DMA_IFCR_CTCIF5;
	}
	
	xQueueSendFromISR(usart_receive_buffer,usart_data_receive_array,0);
}
/*************************************************
Reload DMA Channel 4 
*************************************************/
void DMA_Ch4_Reload(int new_buf_size){
	
	DMA1_Channel4->CCR &= ~DMA_CCR1_EN;
	DMA1_Channel4->CNDTR = new_buf_size;
	DMA1_Channel4->CCR |= DMA_CCR1_EN;
}


