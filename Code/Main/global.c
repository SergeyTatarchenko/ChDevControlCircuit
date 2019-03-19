/*************************************************
* File Name          : global.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : Global parameters,functions
  and sending messages of charging device 		
*************************************************/

#include "global.h"

/************************************************/
/*-----------global variables-------------------*/

/* declared global extern struct for discrete port state */
PortState_REGISTR IO_STATE;
PortState_REGISTR *IO_Pointer;

value_ADC_REGISTR value_ADC;
value_ADC_REGISTR *adc_val;

/* declared global extern struct for analog port state */
AnalogState_REGISTR AIN_State;
AnalogState_REGISTR *AIN_Pointer;
  
/*************************************************
init all system core drivers
*************************************************/
void Core_Init(){
	/*init MCU pins*/
	DifPinInit();
	/*init channel 1 DMA for ADC*/
	DMA_ADC1_Setup();
	/*internal ADC init*/
	ADC_Init();
	/* Init internal timer as PWM */
	PWM_Init();
	/*init hardware I2C module*/
	I2CInit();
	/*usart init*/
	usart_init();
	/*external interrupt init (for MCP23017)*/
	EXTI_Init();
	/*NVIC config */
	NVIC_Init();
	
	/*first config for MCP23017 */
//	MCP23x17_Init();
	
	DMA_USART1_Setup();
	/*disable reset pin on MCP23017*/
	MCP23017_START;
	
		/*not used */
	/*external multiplexor init*/
	//ADG72X_Init();
	/*get adress, start IO model*/
	IO_Pointer =&IO_STATE;
	AIN_Pointer =&AIN_State;
	
	/*adc init*/
	ADC1_On
	adc_val = &value_ADC;

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
set state of chosen pins
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
internal error handler 
*************************************************/
void ResetIO_Model(){
	
	MCP23017_RESET;
	
}

/*************************************************
set output byte of chosen port
*************************************************/
_Bool Set_IO_Byte(uint8_t byte){	
	_Bool state;
	IO_Pointer->OUTPUTS = byte;
	PortA->OLAT = IO_Pointer->OUTPUTS;
	state = MCP23x17_SetOutByte(PortA,byte);
	return state;	
}
/*************************************************
Init different MCU pins
*************************************************/
void DifPinInit(){
	
	/* config  LED on PC13*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~(GPIO_CRH_MODE13|GPIO_CRH_CNF13);	
	GPIOC->CRH |= (GPIO_CRH_MODE13_0  | GPIO_CRH_MODE13_1);	
	
	LED_OFF;
	
	/*config MCP23017 Reset pin*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRL &= ~(GPIO_CRL_MODE5|GPIO_CRL_CNF5);	
	GPIOB->CRL |= (GPIO_CRL_MODE5_0  | GPIO_CRL_MODE5_1);	
	
}
/*************************************************
send USART message, use DMA , medium priority 
*************************************************/
void send_usart_message(uint8_t *message,uint32_t buf_size){
	
	memcpy(USART1_transmit_array,message,buf_size);
	DMA_Ch4_Reload(buf_size);
}                                                                     
/*************************************************
calc adc value, fill struct with mv 
*************************************************/
void adc_calc_value(){
	
	adc_val->CH1_ADC = (ADC1_DataArray[0]*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	adc_val->CH2_ADC = (ADC1_DataArray[1]*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	adc_val->CH3_ADC = (ADC1_DataArray[2]*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	adc_val->CH4_ADC = (ADC1_DataArray[3]*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	adc_val->CH5_ADC = (ADC1_DataArray[4]*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	adc_val->CH6_ADC = (ADC1_DataArray[5]*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	
}
