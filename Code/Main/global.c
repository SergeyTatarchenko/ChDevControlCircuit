/*************************************************
* File Name          : global.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : Global parameters,functions
  and sending messages of charging device 		
*************************************************/


#include "global.h"
#include "mcp23x17.h"
#include "adg72x.h"
/************************************************/
/*-----------global variables-------------------*/
/* declared global extern struct for discrete port state */
PortState_REGISTR IO_STATE;
PortState_REGISTR *IO_Pointer;
/* declared global extern struct for analog port state */
AnalogState_REGISTR AIN_State;
AnalogState_REGISTR *AIN_Pointer;

/*************************************************
init all system core drivers
*************************************************/
void Core_Init(){
	/*init port for led on PC13*/
	LedInit();
	/*init channel 1 DMA for ADC*/
	DMA_ADC1_Setup();
	/*internal ADC init*/
	ADC_Init();
	/* Init internal timer as PWM */
	PWM_Init();
	/*init hardware I2C module*/
	I2C2Init();
	/*first config for MCP23017 */
	MCP23x17_Init();
	/*usart init*/
	usart_init();
	/*external multiplexor init*/
	
	//ADG72X_Init();
	
	/*get adress, start IO model*/
	IO_Pointer =&IO_STATE;
	AIN_Pointer =&AIN_State;

}
/*************************************************
get state of all avaliable IO ports
*************************************************/
_Bool Get_IO_State(){
	_Bool state;
	/* */
	state = MCP23x17_GetState(PORTA);
	/* */
	state &= MCP23x17_GetState(PORTB);
	
	IO_Pointer->OUTPUTS = PortA->GPIO;
	IO_Pointer->INPUTS = PortB->GPIO;
	
	return state;
}
/*************************************************
set state of chosen port
*************************************************/
_Bool Set_IO_State(int pin,int pin_state){
	_Bool state;	
	switch(pin_state){
		case 1:
			IO_Pointer->OUTPUTS |= 1<<pin;
			break;
		case 0:
			IO_Pointer->OUTPUTS &= ~(1<<pin);		
			break;
		default:
			break;
	}
	
	PortA->OLAT = IO_Pointer->OUTPUTS;
	
	state = MCP23x17_SetOutPin(PortA,pin,pin_state);
	return state;
}
/*************************************************
get value from chosen analog input
*************************************************/
_Bool Get_AIn_State(int port){
	_Bool state;
	
	return state;
}
/*************************************************
Init blue LED on board (PC13 pin) 
*************************************************/
void LedInit(){
	/* LED on PC13*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~(GPIO_CRH_MODE13|GPIO_CRH_CNF13);	
	GPIOC->CRH |= (GPIO_CRH_MODE13_0  | GPIO_CRH_MODE13_1);	
}
