/*************************************************
* File Name          : global.h
* Author             : Tatarchenko S.
* Version            : v 1.1
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
 
/*data array for adc*/
uint16_t ADC1_DataArray[ADC1_BUF_SIZE];

uint16_t adc_ch1_buffer[adc_filter_size];
uint16_t adc_ch2_buffer[adc_filter_size];
uint16_t adc_ch3_buffer[adc_filter_size];
uint16_t adc_ch4_buffer[adc_filter_size];
uint16_t adc_ch5_buffer[adc_filter_size];
uint16_t adc_ch6_buffer[adc_filter_size];
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
	usart_speed(56000);
	
	
	/*external interrupt init (for MCP23017)*/
	EXTI_Init();
	/*NVIC config */
	NVIC_Init();
	
	/*first config for MCP23017 */
	MCP23x17_Init();
	
	DMA_USART1_Setup();
	/*disable reset pin on MCP23017*/
	MCP23017_START;
	
	/*bxCAN module config*/
	CAN_init();
	
	/*get adress, start IO model*/
	IO_Pointer =&IO_STATE;	
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
void ResetIO_Model()
{
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
	
	/* config  SYNC LED on PC13*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~(GPIO_CRH_MODE13|GPIO_CRH_CNF13);	
	GPIOC->CRH |= (GPIO_CRH_MODE13_0  | GPIO_CRH_MODE13_1);	
	SYNC_LED_OFF;
	
	/* config  FAULT LED on PB13*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRH &= ~(GPIO_CRH_MODE13|GPIO_CRH_CNF13);	
	GPIOB->CRH |= (GPIO_CRH_MODE13_0  | GPIO_CRH_MODE13_1);	
	FAULT_LED_OFF;
	
	/* config  STATE LED on PB14*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRH &= ~(GPIO_CRH_MODE14|GPIO_CRH_CNF14);	
	GPIOB->CRH |= (GPIO_CRH_MODE14_0  | GPIO_CRH_MODE14_1);	
	STATE_LED_OFF;
	
	/*config MCP23017 Reset pin*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRL &= ~(GPIO_CRL_MODE5|GPIO_CRL_CNF5);	
	GPIOB->CRL |= (GPIO_CRL_MODE5_0  | GPIO_CRL_MODE5_1);	
	
}
/*************************************************
send USART message, use DMA , medium priority 
*************************************************/
void send_usart_message(uint8_t *message,uint32_t buf_size){
	
	if(buf_size <= USART1_DEFAULT_BUF_SIZE){
		memcpy(usart_data_transmit_array,message,buf_size);
		DMA_Ch4_Reload(USART_DATA_TYPE1,buf_size);
	}
	else {
		memcpy(usart_data_stream,message,buf_size);
		DMA_Ch4_Reload(USART_DATA_TYPE2,buf_size);}
}

/*implement of SOM function*/
#ifdef TARGET
void HWOBJ_Event(int obj_id){
	
	OBJ_STRUCT* obj = objDefault + obj_id;
	
	/*output event*/
	if((obj->hardware_adress >= out_0)&&((obj->hardware_adress <= out_7))){
			Set_IO_State((int)(obj->hardware_adress - out_offset),(int)obj->obj_state);
	}
}
#endif
/*************************************************
calc adc value, fill struct with mv 
*************************************************/
void adc_calc_value()
{
	adc_val->CH1_ADC = (ADC1_DataArray[0]*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	adc_val->CH2_ADC = (ADC1_DataArray[1]*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	adc_val->CH3_ADC = (ADC1_DataArray[2]*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	adc_val->CH4_ADC = (ADC1_DataArray[3]*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	adc_val->CH5_ADC = (ADC1_DataArray[4]*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	adc_val->CH6_ADC = (ADC1_DataArray[5]*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	
	adc_val->TEMP_SENSOR = (ADC1_DataArray[6]*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	adc_val->TEMP_SENSOR = (uint16_t)((float)(1430 - adc_val->TEMP_SENSOR)/(float)(4.3) +25);
	
}

/*************************************************
фильтр скользящего среднего для канала АЦП с шумом 
*************************************************/
uint16_t adc_moving_average_filter(uint16_t *buff, uint32_t buff_size)
{
	uint32_t ExpectedValue;
	int counter = 0;
	ExpectedValue = 0;
	
	for(counter = 0 ;counter < buff_size; counter ++){
		ExpectedValue += buff[counter];
	}
	ExpectedValue = ExpectedValue/buff_size;
	return (uint16_t)ExpectedValue;
}
/*************************************************
 Обработка показания  датчика dvl 1000 
*************************************************/
uint16_t get_dvl1000_value(uint16_t adc_voltage)
{
	
	//const int  sensor_load = 82;
	const int  sensor_load = 62;
	const int  sensor_rate = 50;
	/*
	DVL 1000  - 50uA per 1V;
	sensor load  - 82 Omh;
	*/
	/*              get inverted value in mkV       get current   sensor value*/
	int voltage = ((adc_voltage)*1000/sensor_load)/sensor_rate;
	
	return (uint16_t)voltage;
}
/*************************************************
 Обработка показания  датчика lac 300  
*************************************************/
uint16_t get_lac300_value(uint16_t adc_voltage)
{
	
	//const int  sensor_load = 82;
	const int  sensor_load = 62;
	const int  sensor_rate = 3; /*3000/1000 mkA to mA*/
	/*
	DVL 1000  - 33uA per 1A;
	sensor load  - 82 Omh;
	*/
	/*              get inverted value in mkV       get current      sensor value*/
	int current = ((adc_voltage)*1000/sensor_load)*sensor_rate/1000;
	
	return (uint16_t)current;
}
/*************************************************
 Обработка показания  датчика lf510  
*************************************************/
uint16_t get_lf510_value(uint16_t adc_voltage)
{
	
	//const int  sensor_load = 82;
	const int  sensor_load = 62;
	const int  sensor_rate = 2; /*2000/1000 mkA to mA*/
	/*
	LF 510-S  - 20uA per 1A;
	sensor load  - 82 Omh;
	*/
	/*              get inverted value in mkV       get current      sensor value*/
	int current = ((adc_voltage)*1000/sensor_load)*sensor_rate/1000;
	
	return (uint16_t)current;
}

void sync_led_invertor(void)
{
	static int state = 0;
	state = ~state;
	if(state)
	{
		SYNC_LED_ON;
	}
	else
	{
		SYNC_LED_OFF;
	}
}

void state_led_invertor(void)
{
	static int state = 0;
	state = ~state;
	if(state)
	{
		STATE_LED_ON;
	}
	else
	{
		STATE_LED_OFF;
	}
}

void fault_led_invertor(void)
{
	static int state = 0;
	state = ~state;
	if(state)
	{
		FAULT_LED_ON;
	}
	else
	{
		FAULT_LED_OFF;
	}
}

int comparator(int plus, int minus)
{
	if(plus >= minus){
		return 1;
	}else{
		return 0;
	}	
}

uint32_t fabs_function(int a, int b)
{
	if(a > b)
	{
		return (a-b);
	}
	else if(a < b)
	{
		return (b-a);
	}
	else{
		return 0;
	}
}
/*-----------------------------------------------*/
void USART1_IRQHandler(){
	uint8_t buff;
	
	if(USART1->SR &= USART_SR_RXNE){
		
		buff = USART1->DR;
		
		switch(buff){
			/**/
			case START_BYTE_0:
				if(usart_irq_counter == 0){
					usart_data_receive_array[usart_irq_counter] = buff;
					usart_irq_counter++;
					
				}else{
					if((usart_irq_counter < LEN_USART_MSG_OBJ) && (usart_irq_counter > (LEN_HEAD_SIZE -1))){
						usart_data_receive_array[usart_irq_counter] = buff;
						if(usart_irq_counter == (LEN_USART_MSG_OBJ)){
							break;
						}
						usart_irq_counter++;
					}else{
						usart_irq_counter = 0;
					}
				}
				break;
			case START_BYTE_1:
				if(usart_irq_counter == 1){
					usart_data_receive_array[usart_irq_counter] = buff;
					usart_irq_counter++;
				}else{
					if((usart_irq_counter < LEN_USART_MSG_OBJ) && (usart_irq_counter > (LEN_HEAD_SIZE -1))){
						/**/
						usart_data_receive_array[usart_irq_counter] = buff;
						if(usart_irq_counter == (LEN_USART_MSG_OBJ)){
							break;
						}
						usart_irq_counter++;
					}else{
						usart_irq_counter = 0;
					}
				}
				break;	
			case ID_NETWORK:
				if(usart_irq_counter == 2){
					usart_data_receive_array[usart_irq_counter] = buff;
					usart_irq_counter++;
				}else{
					if((usart_irq_counter < LEN_USART_MSG_OBJ) && (usart_irq_counter > (LEN_HEAD_SIZE -1))){
						/**/
						usart_data_receive_array[usart_irq_counter] = buff;
						if(usart_irq_counter == (LEN_USART_MSG_OBJ)){
							break;
						}
						usart_irq_counter++;
					}else{
						usart_irq_counter = 0;
					}
				}
				break;
			/**/	
			case ID_REMOTE_CNTRL:
				if(usart_irq_counter == 3){
					usart_data_receive_array[usart_irq_counter] = buff;
					usart_irq_counter++;
				}else{
					if((usart_irq_counter < LEN_USART_MSG_OBJ) && (usart_irq_counter > (LEN_HEAD_SIZE -1))){
						usart_data_receive_array[usart_irq_counter] = buff;
						
						if(usart_irq_counter == (LEN_USART_MSG_OBJ)){
							break;
						}
						usart_irq_counter++;
					}else{
						usart_irq_counter = 0;
					}
				}
				break;
			/**/	
			default:
				if((usart_irq_counter < LEN_USART_MSG_OBJ) && (usart_irq_counter > (LEN_HEAD_SIZE -1))){
					usart_data_receive_array[usart_irq_counter] = buff;
					if(usart_irq_counter == (LEN_USART_MSG_OBJ)){
							break;
						}
						usart_irq_counter++;
					}else{
						usart_irq_counter = 0;
					}
				break;
		}
		if(usart_irq_counter == (LEN_USART_MSG_OBJ-1)){
			usart_irq_counter = 0;
			xQueueSendFromISR(usart_receive_buffer,usart_data_receive_array,0);	
		}	
	}
}

/*-----------------------------------------------*/
