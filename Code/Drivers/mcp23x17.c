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
	/* config registers mapping set bit BANK = 1*/
	PortConfig->IOCON = 0x80;
	data[0] = IOCONB_ADDR0;
	data[1] = PortConfig->IOCON;
	I2C2SendData(MCP23017_ADRESS,data,sizeof(data));
	
	/* config PortA */
	PortConfig->IODIR   = 0x00;
	PortConfig->IPOL    = 0x00;
	PortConfig->GPINTEN = 0x00;
	PortConfig->DEFVAL  = 0x00;
	PortConfig->INTCON  = 0x00;
	PortConfig->IOCON   = 0x80;
	PortConfig->GPPU    = 0x00;
	
	config[0] = IODIRA_ADDR1;
	memcpy(config+1,PortConfig,sizeof(config));
	I2C2SendData(MCP23017_ADRESS,config,sizeof(config));
	
	/* config PortB */
	PortConfig->IODIR   = 0x00;
	PortConfig->IPOL    = 0x00;
	PortConfig->GPINTEN = 0x00;
	PortConfig->DEFVAL  = 0x00;
	PortConfig->INTCON  = 0x00;
	PortConfig->IOCON   = 0x80;
	PortConfig->GPPU    = 0x00;
	config[0] = IODIRB_ADDR1;
	
	memcpy(config+1,PortConfig,sizeof(config));
	I2C2SendData(MCP23017_ADRESS,config,sizeof(config));
}
/*************************************************
get global state output pin mcp23x17 
*************************************************/
void MCP23x17_GetState(int Port){
	uint8_t data[2] ={0,0};
	switch(Port){
		case PORTA:
			I2C2GetData(MCP23017_ADRESS,GPIOA_ADDR1,data,2);
		    memcpy(PortA,data,sizeof(data));	
			break;
		case PORTB:
			I2C2GetData(MCP23017_ADRESS,GPIOB_ADDR1,data,2);
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

