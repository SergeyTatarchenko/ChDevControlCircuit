/*************************************************
* File Name          : mcp23x17.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : mcp23x17 i2c driver
*************************************************/
#include "mcp23x17.h"
/*-----------local define-----------------------*/

/*-----------local variables--------------------*/
struct EXP_GPIO_PortConfig EXP_GPIO_CONFIG;
struct EXP_GPIO_PortConfig *PortConfig;

struct EXP_GPIO_PortIO EXP_GPIO_A;
struct EXP_GPIO_PortIO *PortA;
struct EXP_GPIO_PortIO EXP_GPIO_B;
struct EXP_GPIO_PortIO *PortB;

struct EXP_GPIO_PortState EXP_STATE_A;
struct EXP_GPIO_PortState *PortAState;
struct EXP_GPIO_PortState EXP_STATE_B;
struct EXP_GPIO_PortState *PortBState;

/*************************************************
init mcp23x17 
*************************************************/
void MCP23x17_Init(void){	
	
	uint8_t data[2];
	/*config array*/
	uint8_t config [8];
	
	PortConfig = &EXP_GPIO_CONFIG;	
	
	PortA = &EXP_GPIO_A;
	PortB = &EXP_GPIO_B;
	
	PortAState = &EXP_STATE_A;
	PortBState = &EXP_STATE_B;
	
	/*default config PORTB (0-3) is input
	PORTA (0-7) is output
	PORTB (4-7) is unused (NC on PCB)*/
	
	/* config registers, segregated mapping,
	   set bit BANK = 1*/
	PortConfig->IOCON = 0x80;
	data[0] = IOCONB_ADDR0;
	data[1] = PortConfig->IOCON;
	I2C2SendData(MCP23017_ADRESS,data,sizeof(data));
	
	/* config PortA,  pins 0-7 config as output,
	   not inverted output, disable interrupt,
	   enable pull up resistor on pins 0-7;	 
		 */
	PortConfig->IODIR   = 0x00;
	PortConfig->IPOL    = 0x00;
	PortConfig->GPINTEN = 0x00;
	PortConfig->DEFVAL  = 0x00;
	PortConfig->INTCON  = 0x00;
	PortConfig->IOCON   = 0x80;
	PortConfig->GPPU    = 0xFF;
	
	config[0] = IODIRA_ADDR1;
	memcpy(config+1,PortConfig,sizeof(config));
	I2C2SendData(MCP23017_ADRESS,config,sizeof(config));
	
	/* config PortB, pins 0-3 is input
	   not inverted input, enable interrupts,pins compare
	   against previous value, pull up enable 
	     */
	PortConfig->IODIR   = 0x0F;
	PortConfig->IPOL    = 0x00;
	PortConfig->GPINTEN = 0x0F;
	PortConfig->DEFVAL  = 0x00;
	PortConfig->INTCON  = 0x00;
	PortConfig->IOCON   = 0x80;
	PortConfig->GPPU    = 0xFF;
	config[0] = IODIRB_ADDR1;
	
	memcpy(config+1,PortConfig,sizeof(config));
	I2C2SendData(MCP23017_ADRESS,config,sizeof(config));
}
/*************************************************
get global state output pin mcp23x17 
*************************************************/
void MCP23x17_GetState(int Port){
	uint8_t data[2] ={0,0};
	/* forced copy of chosen port state and */
	switch(Port){
		case PORTA:
			I2C2GetData(MCP23017_ADRESS,INTFA_ADDR1,data,sizeof(data));
		    memcpy(PortAState,data,sizeof(data));
			I2C2GetData(MCP23017_ADRESS,GPIOA_ADDR1,data,sizeof(data));
		    memcpy(PortA,data,sizeof(data));
			break;
		case PORTB:
			I2C2GetData(MCP23017_ADRESS,INTFB_ADDR1,data,sizeof(data));
			memcpy(PortBState,data,sizeof(data));	
			I2C2GetData(MCP23017_ADRESS,GPIOB_ADDR1,data,sizeof(data));
			memcpy(PortB,data,sizeof(data));	
		break;
		default:
			break;
	}
}
/*************************************************
set state output pin mcp23x17 
*************************************************/
void MCP23x17_SetOutPin(int bit,int state){
	/*output array*/
	uint8_t output [3];
	switch(state){
		case 1:
			PortA->OLAT |= (1<<bit);
			break;
		case 0:
			PortA->OLAT &= ~(1<<bit);
			break;
		default:
			PortA->OLAT &= ~(1<<bit);
			break;
	}
	output[0] = GPIOA_ADDR1;
	memcpy(output+1,PortA,sizeof(output)-1);
	I2C2SendData(MCP23017_ADRESS,output,sizeof(output));
}

