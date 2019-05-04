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
/*define can clock in MHz*/
#define CAN_CLOCK	36
/*----------------------------------------------*/
typedef struct {
	
  uint32_t StdId; 
  uint32_t ExtId;  
  uint8_t IDE;     
  uint8_t RTR;    
  uint8_t DLC;    
  uint8_t Data[8];

} CanTxMsg;

typedef struct{
	
  uint32_t StdId; 
  uint32_t ExtId; 
  uint8_t IDE;    
  uint8_t RTR;    
  uint8_t DLC;    
  uint8_t Data[8];
  uint8_t FMI;  
} CanRxMsg;



#define	can_mode_normal				0
#define	can_mode_loopback			1
#define	can_mode_silent				2
#define	can_mode_silent_loopback	3

/*
	values of BRR, TS1 and TS2 calc in	
	http://www.bittiming.can-wiki.info/ 
*/

#if CAN_CLOCK == 16
	/*can baudrate 250 kb/s ; CAN clock 16 Mhz*/ 	
	#define can_BRR	4
	#define can_TS1	13
	#define can_TS2	2

#elif CAN_CLOCK == 36
	/*can baudrate 250 kb/s ; CAN clock 36 Mhz*/ 	
	#define can_BRR	9
	#define can_TS1	13
	#define can_TS2	2

#endif

/*----------------------------------------------*/

/*-----------global function prototypes---------*/
extern void CAN_init(void);
/*-----------local function prototypes----------*/


static void can_id_filter_config(void);
static void can_set_mode(int mode);
#endif
