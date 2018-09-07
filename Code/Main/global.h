/*************************************************
* File Name          : global.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : global.c header		
*************************************************/
#include "stm32f10x.h"
#include "string.h"
#include "i2c.h"
#include "adc.h"
#include "dma.h"
#include "pwm.h"
#include "usart.h"
/*----------- global typedef---------------------*/

/*state of all io port */
#pragma pack(push,1)
typedef struct{
	union{
		uint8_t PortA_Byte;
		struct{
			unsigned A0:1;
			unsigned A1:1;
			unsigned A2:1;
			unsigned A3:1;
			unsigned A4:1;
			unsigned A5:1;
			unsigned A6:1;
			unsigned A7:1;
			} bit;
		} PortA_Byte_All;	
	union{
		uint8_t PortB_Byte;
		struct{
			unsigned B0:1;
			unsigned B1:1;
			unsigned B2:1;
			unsigned B3:1;
			unsigned B4:1;
			unsigned B5:1;
			unsigned B6:1;
			unsigned B7:1;
			} bit;
		} PortB_Byte_All;		
}PortState_REGISTR;
#pragma pack(pop)

/*----------- global variables-------------------*/
extern PortState_REGISTR IO_STATE;
extern PortState_REGISTR *IO_Pointer;
/*----------- global define----------------------*/

#define	OUTPUTS 	PortA_Byte_All.PortA_Byte 
#define INPUTS		PortB_Byte_All.PortB_Byte 

#ifdef MCP23017_ADRESS
	#define OUT0	0
	#define OUT1	1
	#define OUT2	2
	#define OUT3	3
	#define OUT4	4
	#define OUT5	5
	#define OUT6	6
	#define OUT7	7
#endif

#ifdef IO_B
	#define IN0	PortB_Byte_All.bit.B0
	#define IN1	PortB_Byte_All.bit.B1
	#define IN2	PortB_Byte_All.bit.B2
	#define IN3	PortB_Byte_All.bit.B3
	#define IN4	PortB_Byte_All.bit.B4
	#define IN5	PortB_Byte_All.bit.B5
	#define IN6	PortB_Byte_All.bit.B6
	#define IN7	PortB_Byte_All.bit.B7
#endif

/*-----------local function prototypes----------*/
void LedInit(void);
/*----------- global function prototypes---------*/

/*Тут прототипы готовых функций для работы с ядром и периферийными устройствами */

/*init all peripherals and external circuits*/
extern void Core_Init(void);

/*get state of all available IO ports and puts it in the appropriate structure,
  return true if success*/
extern _Bool Get_IO_State(void);

/*get state of chosen IO port and puts it in the appropriate structure, return
  true if success*/
extern _Bool Set_IO_State(int pin,int pin_state);














