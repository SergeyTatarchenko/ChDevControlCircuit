/*************************************************
* File Name          : can.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : can.c header
*************************************************/
#ifndef CAN_H
#define CAN_H

#include "stm32f10x.h"
#include "system_stm32f10x.h"
#include "string.h"

/*-----------local define-----------------------*/
typedef enum{
	baud_250 = 250,
	baud_500 = 500,
	baud_1000 = 1000,
}can_baudrate;
	
/*-----------global function prototypes---------*/
extern void CAN_init(void);
/*-----------local function prototypes----------*/


static void can_set_baudrate(void);
static void can_set_mode(void);
#endif
