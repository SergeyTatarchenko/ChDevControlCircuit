/*************************************************
* File Name          : adc.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : ADC1 with DMA
*************************************************/
#include "adc.h"
/*************************************************
Init ADC1 function
*************************************************/
void ADC_Init(){
	/* fast ADC on PA1, PA2, PA3, PA4, PA5, PA6 */
	
	if((RCC->APB2ENR&RCC_APB2ENR_IOPAEN)==0){
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	GPIOA->CRL &=~(GPIO_CRL_CNF1|GPIO_CRL_MODE1|	//PA1
				   GPIO_CRL_CNF2|GPIO_CRL_MODE2|	//PA2
				   GPIO_CRL_CNF3|GPIO_CRL_MODE3|	//PA3
				   GPIO_CRL_CNF4|GPIO_CRL_MODE4|	//PA4
				   GPIO_CRL_CNF5|GPIO_CRL_MODE5|	//PA5
				   GPIO_CRL_CNF6|GPIO_CRL_MODE6);	//PA6	
	
	/*ADC1  clock  enable*/
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	/*ADC1 calibration*/
	ADC1->CR2 |= ADC_CR2_CAL;
	while((ADC1->CR2 & ADC_CR2_CAL) == 1);
	
	/*scan mode*/
	ADC1->CR1 |= ADC_CR1_SCAN;
	
	/*cont mode,conversion started from SWSTART bit,
	external trigger conversion enable	*/
	ADC1->CR2 |= (ADC_CR2_CONT|ADC_CR2_EXTSEL|ADC_CR2_EXTTRIG);
		
	/*DMA mode enable*/
	ADC1->CR2 |=ADC_CR2_DMA;	

	/*lenght of channel sequence
	L[3:0] = 101 - 6 conversions*/
	ADC1->SQR1 |= (ADC_SQR1_L_0 | ADC_SQR1_L_2);
	
	/*channel poll sequence*/
	ADC1->SQR3 |=(ADC_SQR3_SQ1_0| //PA1 -1
				  ADC_SQR3_SQ2_1| //PA2 -2
				  ADC_SQR3_SQ3_1|ADC_SQR3_SQ3_0| //PA3 -3
				  ADC_SQR3_SQ4_2| //PA4 -4
				  ADC_SQR3_SQ5_2|ADC_SQR3_SQ5_0| //PA5 -5
		          ADC_SQR3_SQ6_2|ADC_SQR3_SQ6_1); //PA6 -6
	
	/*ADC1 on*/
	ADC1->CR2 |=ADC_CR2_ADON;
}
