/*************************************************
* File Name          : mcp3221.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : mcp3221.c header
*************************************************/
#ifndef MCP3221_H
#define MCP3221_H

#include "global.h"
#include "i2c.h"

/*-----------global define----------------------*/

#ifdef EC_PACKAGE
	#define MCP3221_ADRESS	0x96
#endif

/*12 bit ADC*/
#define ADC_RATE	4095

/* default 5V reference voltage*/
#define ADC_REF		5

/*----------- global function prototypes---------*/
extern _Bool MCP3221_Get_Value(uint8_t *pointer);

#endif
