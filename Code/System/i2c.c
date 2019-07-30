/*************************************************
* File Name          : i2c.c
* Author             : Tatarchenko S.
* Version            : v 1.2
* Description        : I2C bus module for stm32f1x
*************************************************/
#include "i2c.h"

int bus_error = 0;
/*************************************************
Init I2C module, Master mode, speed 400 KHz Fm
*************************************************/
void I2CInit(){
	/*enable clock for I2C2 and GPIOB*/
	RCC->APB1ENR |= RCC_APB1ENR_I2C2EN; 
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;	
	
	GPIOB->CRH |= GPIO_CRH_CNF10;		
	GPIOB->CRH |= (GPIO_CRH_MODE10_1|GPIO_CRH_MODE10_0);	

	GPIOB->CRH |= GPIO_CRH_CNF11;		
	GPIOB->CRH |= (GPIO_CRH_MODE11_1|GPIO_CRH_MODE11_0);
	
	I2C_MODULE->CR1 &= I2C_CR1_SWRST;
	I2C_MODULE->CR1 = (uint32_t)0x00;
	
	/*ack enabled*/
	I2C_MODULE->CR1 = I2C_CR1_ACK;
	
	I2C_MODULE->CR2 |= APB1_FREQ/1000000UL;		
	I2C_MODULE->CCR &=~I2C_CCR_CCR;
	
	/*Fm mode, duty cycle*/
	I2C_MODULE->CCR |= (I2C_CCR_FS|I2C_CCR_DUTY);
	
	I2C_MODULE->CCR |= 6;		// магическое число 1
	I2C_MODULE->TRISE = 19; 	// магическое число 2
	I2C_MODULE->CR1 |= I2C_CR1_PE; 
}
/*************************************************
Send data I2C
*************************************************/
_Bool I2CSendData(uint8_t adress,uint8_t *data,int lenght){
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
	
	if(I2C_ERROR||bus_error){
		return state;
	}
	return !state;
}
///*************************************************
//Get data I2C
//*************************************************/
_Bool I2CGetData (uint8_t chip_adress,uint8_t adress_byte, uint8_t *data,int lenght){
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
	
	if(I2C_ERROR||bus_error){
		return state;
	}
	return !state;
}
/*************************************************
Send start bit I2C
*************************************************/
void I2CSendStart(){
	int TimeOut = I2C_TimeOut;
	I2C_MODULE->CR1 |= I2C_CR1_START; //send start bit
	while((((I2C_MODULE->SR1 & I2C_SR1_SB) == 0) &&!I2C_ERROR)){
		TimeOut --;
		if(TimeOut<0){
			bus_error = 1;
			break;
		}
	}
}
/*************************************************
Send adress byte I2C
*************************************************/
void I2CSendAdress(uint8_t adress){
	int TimeOut = I2C_TimeOut;
	(void) I2C2->SR1;
	I2C_MODULE->DR =(uint8_t)adress;
	while(!(I2C_MODULE->SR1 & I2C_SR1_ADDR) &&!I2C_ERROR){
		TimeOut --;
		if(TimeOut<0){
			bus_error = 1;
			break;
		}
	}
	(void) I2C_MODULE->SR1;
	(void) I2C_MODULE->SR2;
}
/*************************************************
Send byte I2C
*************************************************/
void I2CSendByte(uint8_t byte){
	int TimeOut = I2C_TimeOut;
	I2C_MODULE->DR = (uint8_t)byte;
	while(!(I2C_MODULE->SR1 & I2C_SR1_BTF) &&!I2C_ERROR){
		TimeOut --;
		if(TimeOut<0){
			bus_error = 1;
			break;
		}
	}
}
/*************************************************
Get byte I2C
*************************************************/
uint8_t I2CGetByte(){
	int TimeOut = I2C_TimeOut;
	uint8_t data;
	while(!(I2C_MODULE->SR1 & I2C_SR1_RXNE)&&!I2C_ERROR){
		TimeOut --;
		if(TimeOut<0){
			bus_error = 1;
			break;
		}
	}
	data = I2C_MODULE->DR;
	return data;
}
/*************************************************
Send stop bit I2C
*************************************************/
void I2CSendStop(){
	int TimeOut = I2C_TimeOut;
	I2C_MODULE->CR1 |= I2C_CR1_STOP;
	while(((I2C_MODULE->SR2 & I2C_SR2_BUSY)!=0) &&!I2C_ERROR){
		TimeOut --;
		if(TimeOut<0){
			bus_error = 1;
			break;
		}
	} 
}

/******************* end of file ****************/
