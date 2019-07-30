/*************************************************
* File Name          : mcp3221.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : mcp3221 I2C driver (external
					   ADC)
*************************************************/
#include "mcp3221.h"

/*************************************************
get analog value from ADC and puts it in the array 
*************************************************/
_Bool MCP3221_Get_Value(uint8_t *pointer){
	_Bool state;
	
	state = I2CGetData(MCP3221_ADRESS,NULL,pointer,2);
	
	return state;	
}
