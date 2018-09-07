/*************************************************
* File Name          : i2c.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : i2c.c header
*************************************************/
#include "stm32f10x.h"
#include "system_stm32f10x.h"
/*-----------local define-----------------------*/
#define I2C_SPEED	400000UL
#define I2C_TimeOut	1000UL
#define I2C_ERROR	\
	((I2C2->SR1 & I2C_SR1_TIMEOUT)\
	||(I2C2->SR1 & I2C_SR1_BERR)\
	||(I2C2->SR1 & I2C_SR1_ARLO)\
	||(I2C2->SR1 & I2C_SR1_AF)\
	||(I2C2->SR1 & I2C_SR1_OVR)\
	||(I2C2->SR1 & I2C_SR1_PECERR))	
	/*1 SCL лежит в земле;
	  2 START или STOP в неверное время;
	  3 Потеря арбитража;
      4 Нет ответа от слейва/ов;
      5 Переполнение буфера данных;
	  6 Ошибка приема PEC*/
/*-----------global function prototypes---------*/
extern void I2C2Init(void);
extern _Bool	I2C2SendData(uint8_t adress,uint8_t *data,int lenght);
extern _Bool	I2C2GetData (uint8_t chip_adress,uint8_t adress_byte, uint8_t *data,int lenght);
/*-----------local function prototypes----------*/
extern void I2CSendStart(void);
extern void I2CSendAdress( uint8_t adress);
extern void I2CSendByte(uint8_t data);
extern uint8_t I2CGetByte(void);
extern void I2CSendStop(void);
