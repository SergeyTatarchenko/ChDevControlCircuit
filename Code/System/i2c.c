/*************************************************
* File Name          : i2c.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : I2C bus module
*************************************************/
#include "i2c.h"
/*************************************************
Init I2C2 module, Master mode, speed 400 KHz Fm
*************************************************/
void I2C2Init(){
	/*enable clock for I2C2 and GPIOB*/
	RCC->APB1ENR |= RCC_APB1ENR_I2C2EN; 
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;	
	
	GPIOB->CRH |= GPIO_CRH_CNF10;		
	GPIOB->CRH |= (GPIO_CRH_MODE10_1|GPIO_CRH_MODE10_0);	

	GPIOB->CRH |= GPIO_CRH_CNF11;		
	GPIOB->CRH |= (GPIO_CRH_MODE11_1|GPIO_CRH_MODE11_0);
	
	I2C2->CR1 &= I2C_CR1_SWRST;
	I2C2->CR1 = (uint32_t)0x00;
	
	/*ack enabled*/
	I2C2->CR1 = I2C_CR1_ACK;
	
	I2C2->CR2 |= APB1_FREQ/1000000UL;		
	I2C2->CCR &=~I2C_CCR_CCR;
	
	/*Fm mode, duty cycle*/
	I2C2->CCR |= (I2C_CCR_FS|I2C_CCR_DUTY);
	
	I2C2->CCR |= 6;		// магическое число 1
	I2C2->TRISE = 19; 	// магическое число 2
	I2C2->CR1 |= I2C_CR1_PE; 
}
/*************************************************
Send data I2C
*************************************************/
_Bool I2C2SendData(uint8_t adress,uint8_t *data,int lenght){
	_Bool state = 0;
	int i = 0;
	I2CSendStart();
	I2CSendAdress(adress);
	if(lenght < 2) {
		I2CSendByte(*data);
	}
	else{
		for(i = 0; i< lenght;i++){
		I2CSendByte(data[i]);
		}
	}
	I2CSendStop();
	
	if(I2C_ERROR){
		return state;
	}
	return !state;
}
///*************************************************
//Get data I2C
//*************************************************/
_Bool I2C2GetData (uint8_t chip_adress,uint8_t adress_byte, uint8_t *data,int lenght){
	_Bool state = 0;
	int i;
	I2CSendStart();
	I2CSendAdress(chip_adress); /*R/W = 0 ; Write*/
	
	/*send adress of first byte to read(if needed)*/
	if(adress_byte!= NULL){
		I2CSendByte(adress_byte);
	}
	I2CSendStop();
	/*restart transmit*/
	I2CSendStart();
	I2CSendAdress(chip_adress|1);/*R/W = 1 ; Read*/
	if(lenght<2){
		*data = I2CGetByte();
	}
	else{
		for(i=0;i<lenght;i++){
			data[i] = I2CGetByte();
		}	
	}
	I2CSendStop();
	
	if(I2C_ERROR){
		return state;
	}
	return !state;
}
/*************************************************
Send start bit I2C
*************************************************/
void I2CSendStart(){
	I2C2->CR1 |= I2C_CR1_START; //send start bit
	while(((I2C2->SR1 & I2C_SR1_SB) == 0)||I2C_ERROR);
}
/*************************************************
Send adress byte I2C
*************************************************/
void I2CSendAdress(uint8_t adress){
	(void) I2C2->SR1;
	I2C2->DR =(uint8_t)adress;
	while(!(I2C2->SR1 & I2C_SR1_ADDR)||I2C_ERROR);
	(void) I2C2->SR1;
	(void) I2C2->SR2;
}
/*************************************************
Send byte I2C
*************************************************/
void I2CSendByte(uint8_t byte){
	I2C2->DR = (uint8_t)byte;
	while(!(I2C2->SR1 & I2C_SR1_BTF)||I2C_ERROR);
}
/*************************************************
Get byte I2C
*************************************************/
uint8_t I2CGetByte(){
	uint8_t data;
	while(!(I2C2->SR1 & I2C_SR1_RXNE)||I2C_ERROR);
	data = I2C2->DR;
	return data;
}
/*************************************************
Send stop bit I2C
*************************************************/
void I2CSendStop(){
	I2C2->CR1 |= I2C_CR1_STOP;
	while(((I2C2->SR2 & I2C_SR2_BUSY)!=0)||I2C_ERROR); 
}





