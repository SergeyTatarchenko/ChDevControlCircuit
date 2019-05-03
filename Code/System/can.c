/*************************************************
* File Name          : can.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : CAN 2.0b bus module for stm32f1x
*************************************************/
#include "can.h"

/*************************************************
Init CAN
*************************************************/
void CAN_init(){
	
	/*enable clock for CAN */
	RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
	
	/*enable clock for AFIO and GPIOA*/	
	RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN|RCC_APB2ENR_AFIOEN);
	
	/*
	  CAN RX on PA11 ; CAN TX on PA12
	  CAN TX - Alternate function push-pull;
	  CAN RX - Input floating / Input pull-up;
	*/
	
	GPIOA->CRH &= ~(GPIO_CRH_MODE11|GPIO_CRH_CNF11);
	GPIOA->CRH |= (GPIO_CRH_MODE11|GPIO_CRH_CNF11_1);//PA11
	GPIOA->CRH &= ~(GPIO_CRH_MODE12|GPIO_CRH_CNF12);
	GPIOA->CRH |= GPIO_CRH_CNF12_1;					 //PA12
	
	/*init can module*/
	
}

/*************************************************
set can baudrate
*************************************************/
static void can_set_baudrate(){
	
}

static void can_set_mode(){
	
}
