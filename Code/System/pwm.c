/*************************************************
* File Name          : pwm.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : PWM module 2 channels
*************************************************/
#include "pwm.h"

/*************************************************
Setup PWM mode for TIM3 CH3/CH4  
*************************************************/
void PWM_Init(){
	
	RCC->APB2ENR |=(RCC_APB2ENR_IOPBEN |RCC_APB2ENR_AFIOEN);
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	
	/*PWM1 on PB0 and PWM2 on PB1*/
	GPIOB->CRL &=~(GPIO_CRL_MODE0|GPIO_CRL_MODE1|
				   GPIO_CRL_CNF1|GPIO_CRL_CNF0);
	
	GPIOB->CRL |=(GPIO_CRL_CNF0_1|GPIO_CRL_MODE0|	//PB0 AF PP
				  GPIO_CRL_CNF1_1|GPIO_CRL_MODE1);	//PB1 AF PP
	
	TIM3->CCER |= (TIM_CCER_CC3E | TIM_CCER_CC3P|
	               TIM_CCER_CC4E | TIM_CCER_CC4P);
	
	/*prescaler value*/
	TIM3->PSC = TIM3_PSC;
	
	/*auto-reload value*/
	TIM3->ARR = PERIOD_PWM;
	
	/*main output enable*/
	TIM3->BDTR |= TIM_BDTR_MOE;
	
  TIM3->CCMR2 = (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1|TIM_CCMR2_OC3M_0|
	             TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1|TIM_CCMR2_OC4M_0);
}

/*************************************************
Set PWM value for TIM1 CH3/CH4
2 channels together
*************************************************/
void PWMSetValue(uint16_t value){
	
	if((value<PWM_MAX_VALUE) && (value>0)){
		
		TIM3->CCR3 = (uint16_t)value;
		/*выделить в отдельную функцию по необходимости*/
		TIM3->CCR4 = (uint16_t)value;
	}
}
