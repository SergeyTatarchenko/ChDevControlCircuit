/*************************************************
* File Name          : i2c.h
* Author             : Tatarchenko S.
* Version            : v 1.2
* Description        : i2c.c header
*************************************************/
#ifndef I2C_H
#define I2C_H

#include "stm32f10x.h"
#include "system_stm32f10x.h"
#include "string.h"
/*-----------local define-----------------------*/
#define I2C_MODULE	I2C2
#define I2C_SPEED	400000UL
#define I2C_TimeOut	PLL_FREQ/1000;

#define I2C_ERROR	\
	((I2C_MODULE->SR1 & I2C_SR1_TIMEOUT)\
	||(I2C_MODULE->SR1 & I2C_SR1_BERR)\
	||(I2C_MODULE->SR1 & I2C_SR1_ARLO)\
	||(I2C_MODULE->SR1 & I2C_SR1_AF)\
	||(I2C_MODULE->SR1 & I2C_SR1_OVR)\
	||(I2C_MODULE->SR1 & I2C_SR1_PECERR))	
	/*1 SCL лежит в земле;
	  2 START или STOP в неверное время;
	  3 Потеря арбитража;
      4 Нет ответа от слейва/ов;
      5 Переполнение буфера данных;
	  6 Ошибка приема PEC*/
/*-----------global function prototypes---------*/
extern void I2CInit(void);
extern _Bool	I2CSendData(uint8_t adress,uint8_t *data,int lenght);
extern _Bool	I2CGetData (uint8_t chip_adress,uint8_t adress_byte, uint8_t *data,int lenght);
/*-----------local function prototypes----------*/
extern void I2CSendStart(void);
extern void I2CSendAdress( uint8_t adress);
extern void I2CSendByte(uint8_t data);
extern uint8_t I2CGetByte(void);
extern void I2CSendStop(void);

extern int bus_error;
#endif
