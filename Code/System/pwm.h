/*************************************************
* File Name          : pwm.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : pwm.c header
*************************************************/
#ifndef PWM_H
#define PWM_H


#include "stm32f10x.h"
#include "system_stm32f10x.h"
/*-----------local define-----------------------*/
#define	TIM3_CLK	APB1_FREQ
#define	TIM3_PSC	TIM3_CLK/100000UL	// get 10MHz timer freq
#define PWM_MAX_VALUE	1000
/*добавить PERIOD_PWM как глобальную переменную-параметр 
  зарядного устройства. */
#define	PERIOD_PWM	1000UL				  // 5 kHz PWM 	
#define PWM_ON	(TIM3->CR1 |= TIM_CR1_CEN);
#define PWM_OFF	(TIM3->CR1 &= ~TIM_CR1_CEN);

#define PWM_PIN0_ON		(GPIOB->BSRR |= GPIO_BSRR_BS0)
#define PWM_PIN0_OFF	(GPIOB->BSRR |= GPIO_BSRR_BR0)

/*-----------global function prototypes---------*/
extern void PWM_Init(void);
extern void PWMSetValue(uint16_t value); 

#endif
