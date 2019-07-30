/*************************************************
* File Name          : ext.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : external and internal
	interrupt control and semaphore handlers
*************************************************/
#include "ext.h"
/************************************************
EXTI 5-19 line handler
*************************************************/
void EXTI9_5_IRQHandler(){
	
	static portBASE_TYPE xTaskWoken = pdFALSE;
	
	EXTI->PR |=EXTI_PR_PR7;
	EXTI->PR |=EXTI_PR_PR6;
	
	xSemaphoreGiveFromISR(InputEvent,&xTaskWoken);
	
	if(xTaskWoken == pdTRUE){
		taskYIELD();
	}
}
/************************************************
NVIC config
*************************************************/
void NVIC_Init(){
	
	/*enable external interrupt on NVIC*/
	NVIC_EnableIRQ (EXTI9_5_IRQn);
	
	
	/*DMA transfer complete interrupt on NVIC*/
	NVIC_EnableIRQ (DMA1_Channel4_IRQn);
			
	NVIC_SetPriority (EXTI9_5_IRQn, 2);
	NVIC_SetPriority (DMA1_Channel4_IRQn, 3);
	NVIC_SetPriority (USART1_IRQn, 3);
	
	/*enable global interrupt*/
	__enable_irq ();
}
/************************************************
config external interrupts
*************************************************/
void EXTI_Init(){
	
	GPIOB->CRL &= ~(GPIO_CRL_CNF7|GPIO_CRL_CNF6|GPIO_CRL_MODE7|GPIO_CRL_MODE6);
	/*input with pull up/down*/
	GPIOB->CRL |= (GPIO_CRL_CNF7_1|GPIO_CRL_CNF6_1);
	
	GPIOB->BSRR |=GPIO_BSRR_BR6;
	GPIOB->BSRR |=GPIO_BSRR_BR7;
	
	
	/*connect EXTI line to PB6 and PB7 */
	AFIO->EXTICR[1] |= AFIO_EXTICR2_EXTI7_PB|AFIO_EXTICR2_EXTI6_PB;
	
	/*rising trigger event for line 6 and 7*/
	EXTI->RTSR |= EXTI_RTSR_TR6|EXTI_RTSR_TR7;
	
	
	/*enable interrupts for EXTI line 6 and 7*/
	EXTI_ENABLE;
}
