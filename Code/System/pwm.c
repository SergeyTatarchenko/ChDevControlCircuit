/*************************************************
* File Name          : pwm.c
* Author             : Tatarchenko S.
* Version            : v 1.2
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

	/*prescaler value*/
	TIM3->PSC = TIM3_PSC;
	
	/*main output enable*/
	TIM3->BDTR |= TIM_BDTR_MOE;
  
  /*PWM mode 1 */	
  TIM3->CCMR2 = (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1|
	             TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1);
}

/*set active PWM channel */
void PWMSetActiveChannel(PWM_CHANNEL channel){
	int active_channel = (int)channel;
	
	PWM_OFF;
	switch(active_channel){
		case CH3:
			TIM3->CCER |= (TIM_CCER_CC3E);
			break;
		case CH4:
			TIM3->CCER |= (TIM_CCER_CC4E);
			break;
		case ALL_CH_OFF:
				TIM3->CCER &= ~(TIM_CCER_CC3E | TIM_CCER_CC3P|
								TIM_CCER_CC4E | TIM_CCER_CC4P);
			break;
		case ALL_CH_ON:
			TIM3->CCER |= (TIM_CCER_CC3E);
			TIM3->CCER |= (TIM_CCER_CC4E);
			break;
		default:
			TIM3->CCER &= ~(TIM_CCER_CC3E | TIM_CCER_CC3P|
							TIM_CCER_CC4E | TIM_CCER_CC4P);
			break;
	}
}
/* PWM frequency config get value in Hz*/
void PWMSetFrequency(int frequency){
	int TimerFrequency = 1000000;
	int prescaler = 0;
	PWM_OFF;
	prescaler = TimerFrequency/frequency;
	/*auto-reload value*/
	TIM3->ARR = (uint16_t)prescaler;
}
/*************************************************
Set PWM value for TIM3 CH3/CH4
*************************************************/
void PWMSetValue(PWM_CHANNEL channel,uint16_t value){
	int setup_value;
	int max_value = TIM3->ARR;
	
	if((value <= PWM_MAX_VALUE) && (value>0)){
		setup_value = (value*max_value)/PWM_MAX_VALUE;
		
		if(channel == CH3){
			TIM3->CCR3 = (uint16_t)setup_value;
			return;
		}
		if(channel == CH4){
			TIM3->CCR4 = (uint16_t)setup_value;
			return;
		}
		if(channel == ALL_CH_ON){
			TIM3->CCR3 = (uint16_t)setup_value;
			TIM3->CCR4 = (uint16_t)setup_value;
		}
	}else{
		TIM3->CCR4 = 0;
		TIM3->CCR3 = 0;
	}
}

extern uint16_t GetDutyCycle(PWM_CHANNEL channel)
{
	if(channel == CH3)
	{
		return TIM3->CCR3;
	}
	if(channel == CH4)
	{
		return TIM3->CCR4;
	}
	return 0;
}
