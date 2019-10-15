/*************************************************
* File Name          : pwm.h
* Author             : Tatarchenko S.
* Version            : v 1.2
* Description        : pwm.c header
*************************************************/
#ifndef PWM_H
#define PWM_H


#include "stm32f10x.h"
#include "system_stm32f10x.h"
/*-----------local define-----------------------*/
#define	TIM3_CLK	APB2_FREQ
#define	TIM3_PSC	TIM3_CLK/1000000UL	// get 1 MHz timer freq
#define PWM_MAX_VALUE	1000

/*добавить PERIOD_PWM как глобальную переменную-параметр 
  зарядного устройства. */

#define	PERIOD_PWM	1000UL

#define PWM_ON	(TIM3->CR1 |= TIM_CR1_CEN);
#define PWM_OFF	(TIM3->CR1 &= ~TIM_CR1_CEN);

#define PWM_PIN0_ON		(GPIOB->BSRR |= GPIO_BSRR_BS0)
#define PWM_PIN0_OFF	(GPIOB->BSRR |= GPIO_BSRR_BR0)

#define PWM_PIN1_ON		(GPIOB->BSRR |= GPIO_BSRR_BS1)
#define PWM_PIN1_OFF	(GPIOB->BSRR |= GPIO_BSRR_BR1)


typedef enum{

	CH3 = 3,
	CH4 = 4,	
	ALL_CH_OFF = 99,
	ALL_CH_ON = 100 /*WARNING - short circuit possible!!!*/
	
}PWM_CHANNEL;

/*-----------global function prototypes---------*/

extern void PWM_Init(void);
extern void PWMSetValue(PWM_CHANNEL channel,uint16_t value); 
extern void PWMSetActiveChannel(PWM_CHANNEL channel);
extern void PWMSetFrequency(int frequency);
extern uint16_t GetDutyCycle(PWM_CHANNEL channel);

#endif
