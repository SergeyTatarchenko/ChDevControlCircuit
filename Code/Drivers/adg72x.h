/*************************************************
* File Name          : adg72x.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : adg72x.c header
*************************************************/
#ifndef ADG72X_H
#define ADG72X_H

#include "string.h"
#include "i2c.h"

/*-----------global typedef---------------------*/
#pragma pack(push,1)
typedef union {
	struct{
		unsigned IN0:1;
		unsigned IN1:1;
		unsigned IN2:1;
		unsigned IN3:1;
		unsigned IN4:1;
		unsigned IN5:1;
		unsigned IN6:1;
		unsigned IN7:1;
	}bit;
	uint8_t byte;
}EXP_Analog_Input;
#pragma pack(pop)
/*-----------global define----------------------*/
#define ADG729_ADRESS 0x9E
/*-----------global variables-------------------*/
extern EXP_Analog_Input AnalogInputs;
extern EXP_Analog_Input *AnalogPortPointer;
/*----------- global function prototypes--------*/
extern void ADG72X_Init(void);
extern _Bool ADG72X_SetInput(int port);

#endif
