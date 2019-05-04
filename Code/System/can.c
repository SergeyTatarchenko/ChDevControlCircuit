/*************************************************
* File Name          : can.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : bxCAN  bus module for stm32f1x
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
	can_set_mode(can_mode_loopback);
}

/*************************************************
 global CAN and baudrate config 
*************************************************/
static void can_set_mode(int mode){
	
	/*enter init mode*/
	CAN1->MCR |= CAN_MCR_INRQ;
	while((CAN1->MSR & CAN_MSR_INAK)==0);
	/*
	Time Triggered Communication Mode disable;
	Set the no automatic retransmission disable;
	Set the receive FIFO locked mode disable;
	*/
	CAN1->MCR &=~(CAN_MCR_TTCM|CAN_MCR_NART|CAN_MCR_RFLM);
	/*
	Set the automatic bus-off management enable;
	Set the automatic wake-up mode enable;
	Set the transmit FIFO priority enable;
	*/
	CAN1->MCR |=(CAN_MCR_TTCM|CAN_MCR_AWUM|CAN_MCR_TXFP);
	/*set can mode*/
	CAN1->BTR &= ~(CAN_BTR_BRP|CAN_BTR_TS1|CAN_BTR_TS2|CAN_BTR_SJW);
	
	CAN1->BTR |= ((uint32_t)mode<<30)|
				 ((uint32_t)(can_TS1-1)<<16)|
				 ((uint32_t)(can_TS2-1)<<20)|
				  (uint32_t)(can_BRR-1);
		
}


static void can_id_filter_config(){
	
	
}





