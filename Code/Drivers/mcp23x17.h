/*************************************************
* File Name          : mcp23x17.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : mcp23x17.c header
*************************************************/
#include "stm32f10x.h"
#include "string.h"
#include "i2c.h"
/*-----------global define----------------------*/
#define MCP23017_ADRESS 0x4E
/*mcp23x17 registers adress from datasheet------*/
#define IODIRA_ADDR0	0x00
#define IODIRB_ADDR0	0x01
#define IPOLA_ADDR0		0x02
#define IPOLB_ADDR0		0x03
#define GPINTENA_ADDR0	0x04
#define GPINTENB_ADDR0	0x05
#define DEFVALA_ADDR0	0x06
#define DEFVALB_ADDR0	0x07
#define INTCONA_ADDR0	0x08
#define INTCONB_ADDR0	0x09
#define IOCONA_ADDR0	0x0A
#define IOCONB_ADDR0	0x0B
#define GPPUA_ADDR0		0x0C
#define GPPUB_ADDR0		0x0D
#define INTFA_ADDR0		0x0E
#define INTFB_ADDR0		0x0F
#define INTCAPA_ADDR0	0x10
#define INTCAPB_ADDR0	0x11
#define GPIOA_ADDR0		0x12
#define GPIOB_ADDR0		0x13
#define OLATA_ADDR0		0x14
#define OLATB_ADDR0		0x14

/*----------------------------------------------*/

#define IODIRA_ADDR1	0x00
#define IPOLA_ADDR1		0x01
#define GPINTENA_ADDR1	0x02
#define DEFVALA_ADDR1	0x03
#define INTCONA_ADDR1	0x04
#define IOCONA_ADDR1	0x05
#define GPPUA_ADDR1		0x06
#define INTFA_ADDR1		0x07
#define INTCAPA_ADDR1	0x08
#define GPIOA_ADDR1		0x09
#define OLATA_ADDR1		0x0A

#define IODIRB_ADDR1	0x10
#define IPOLB_ADDR1		0x11
#define GPINTENB_ADDR1	0x12
#define DEFVALB_ADDR1	0x13
#define INTCONB_ADDR1	0x14
#define IOCONB_ADDR1	0x15
#define GPPUB_ADDR1		0x16
#define INTFB_ADDR1		0x17
#define INTCAPB_ADDR1	0x18
#define GPIOB_ADDR1		0x19
#define OLATB_ADDR1		0x1A

/*----------------------------------------------*/
/*outputs*/
#define PORTA	0	
/*inputs*/
#define PORTB	1
/*-----------global typedef----------------------*/
#pragma pack(push,1)
struct EXP_GPIO_PortConfig{
	uint8_t IODIR;
	uint8_t IPOL;
	uint8_t GPINTEN;
	uint8_t DEFVAL;
	uint8_t INTCON;
	uint8_t IOCON;
	uint8_t GPPU;
};
#pragma pack(pop)
/*----------------------------------------------*/
#pragma pack(push,1)
struct EXP_GPIO_PortState{
	uint8_t INTF;
	uint8_t INTCAP;
};
#pragma pack(pop)
/*----------------------------------------------*/
#pragma pack(push,1)
struct EXP_GPIO_PortIO{
	uint8_t GPIO;
	uint8_t OLAT;
};
#pragma pack(pop)
/*-----------global variables-------------------*/
extern struct EXP_GPIO_PortConfig EXP_GPIO_CONFIG;
extern struct EXP_GPIO_PortConfig *PortConfig;

extern struct EXP_GPIO_PortIO EXP_GPIO_A;
extern struct EXP_GPIO_PortIO *PortA;
extern struct EXP_GPIO_PortIO EXP_GPIO_B;
extern struct EXP_GPIO_PortIO *PortB;

extern struct EXP_GPIO_PortState EXP_STATE_A;
extern struct EXP_GPIO_PortState *PortAState;
extern struct EXP_GPIO_PortState EXP_STATE_B;
extern struct EXP_GPIO_PortState *PortBState;

/*----------- global function prototypes---------*/
extern void MCP23x17_Init(void);
extern void MCP23x17_GetState(int Port);
extern void MCP23x17_SetOutPin(int bit,int state);
/*-----------local function prototypes----------*/
