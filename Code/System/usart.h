/*************************************************
* File Name          : usart.h
* Author             : Kukha M.
* Version            : v 1.0
* Date				 : 11.08.2018
* Description        : 
*************************************************/
#ifndef _USART_H_
#define _USART_H_



#include "stm32f10x.h"
#include "system_stm32f10x.h"


extern void usart_init(void);
extern uint8_t	usart_rx(uint8_t usart_port);
extern void usart_tx(uint8_t *bytes, uint8_t length);

#endif
