/*************************************************
* File Name          : adg72x.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : adg729 i2c driver
*************************************************/
#include "adg72x.h"
/*-----------local define-----------------------*/
/*-----------local variables--------------------*/

EXP_Analog_Input AnalogInputs;
EXP_Analog_Input *AnalogPortPointer;

/*************************************************
init adg729 
*************************************************/
void ADG72X_Init(){
	uint8_t *pointer;
	
	AnalogPortPointer = &AnalogInputs;
	AnalogPortPointer->byte = 0;
	
	memcpy(pointer,AnalogPortPointer,sizeof(unsigned char));
	I2C2SendData(ADG729_ADRESS,pointer,sizeof(unsigned char));
}
/*************************************************
chose analog input for external ADC
*************************************************/
_Bool ADG72X_SetInput(int port){
	uint8_t *pointer;
	_Bool state;
	AnalogPortPointer->byte &= (1<<port);
	
	memcpy(pointer,AnalogPortPointer,sizeof(unsigned char));
	state = I2C2SendData(ADG729_ADRESS,pointer,sizeof(unsigned char));
	
	return state;	
	
}
