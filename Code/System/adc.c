/*************************************************
* File Name          : adc.c
* Author             : Tatarchenko S.
* Version            : v 1.1
* Description        : ADC1 with DMA
*************************************************/
#include "adc.h"
#include "termo.h"

static const uint16_t termo_table[]={_thermistor_};
/*************************************************
Init ADC1 function
*************************************************/
void ADC_Init()
{
	/* fast ADC on PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7 */	
	if((RCC->APB2ENR&RCC_APB2ENR_IOPAEN)==0)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	GPIOA->CRL &=~(GPIO_CRL_CNF0|GPIO_CRL_MODE0|	//PA0
				   GPIO_CRL_CNF1|GPIO_CRL_MODE1|	//PA1
				   GPIO_CRL_CNF2|GPIO_CRL_MODE2|	//PA2
				   GPIO_CRL_CNF3|GPIO_CRL_MODE3|	//PA3
				   GPIO_CRL_CNF4|GPIO_CRL_MODE4|	//PA4
				   GPIO_CRL_CNF5|GPIO_CRL_MODE5|	//PA5
				   GPIO_CRL_CNF6|GPIO_CRL_MODE6|	//PA6
				   GPIO_CRL_CNF7|GPIO_CRL_MODE7		//PA7
				   );
	/*ADC1  clock  enable*/
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	/*scan mode*/
	ADC1->CR1 |= ADC_CR1_SCAN;
	
	/*cont mode,conversion started from SWSTART bit,
	external trigger conversion enable	*/
	ADC1->CR2 |= (ADC_CR2_CONT|ADC_CR2_EXTSEL|ADC_CR2_EXTTRIG);
		
	/*DMA mode enable*/
	ADC1->CR2 |=ADC_CR2_DMA;
	
	/*Temperature Sensor and VREFINT Enable*/
	ADC1->CR2 |=ADC_CR2_TSVREFE;
	ADC1->SMPR1 |= ADC_SMPR1_SMP16_1;
	/*ADC sample time  13.5 cycles */
	ADC1->SMPR2 |= (ADC_SMPR2_SMP0_1|ADC_SMPR2_SMP1_1|ADC_SMPR2_SMP2_1|ADC_SMPR2_SMP3_1|
					ADC_SMPR2_SMP4_1|ADC_SMPR2_SMP5_1|ADC_SMPR2_SMP6_1|ADC_SMPR2_SMP7_1);
	/*lenght of channel sequence*/
	ADC1->SQR1 &= ~ADC_SQR1_L;
	ADC1->SQR1 |= (num_of_adc_conversion - 1)<<20;
	/*channel poll sequence*/
	ADC1->SQR3 |= ((0<<0)|(1<<5)|(2<<10)|(3<<15)|(4<<20)|(5<<25));
	ADC1->SQR2 |= ((6<<0)|(7<<5)|(16<<10));	
	/*ADC1 on*/
	ADC1->CR2 |=ADC_CR2_ADON;	
	/*ADC1 calibration*/	
	ADC1->CR2 |= ADC_CR2_CAL;
	while((ADC1->CR2 & ADC_CR2_CAL) == 1);
}

int16_t ADC_B57045_1K21 (uint16_t val)
{
	int i = 0; 
	for(i = 0;i < 33;i++)
	{
		if(termo_table[i] > val)
		{
			break;
		}
	}
	/*y = 5x-40 */
	return (int16_t)(i*5 - 40);	
}


