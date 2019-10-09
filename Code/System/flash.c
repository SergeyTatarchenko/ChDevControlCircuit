/*************************************************
* File Name          : flash.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : module for STM32 flash erase/read/write
*************************************************/
#include "flash.h"

void flash_unlock()
{
	FLASH->KEYR = FLASH_ACCESS_WORD0;
	FLASH->KEYR = FLASH_ACCESS_WORD1;
}

void flash_lock()
{
	FLASH->CR |= FLASH_CR_LOCK;
}

void flash_erase_page(uint32_t adress)
{
	while (FLASH->SR & FLASH_SR_BSY);
	
	if (FLASH->SR & FLASH_SR_EOP) {
		FLASH->SR = FLASH_SR_EOP;
	}
	
	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR = adress;
	FLASH->CR |= FLASH_CR_STRT;
	
	while (!(FLASH->SR & FLASH_SR_EOP));
	FLASH->SR = FLASH_SR_EOP;
	FLASH->CR &= ~FLASH_CR_PER;
}


int flash_write_page(uint8_t* data, uint32_t address, uint32_t count)
{
	uint8_t *buff = data;	
	if(count%2 != 0)
	{
		return 0;
	}
	/*waiting for flash*/
	while (FLASH->SR & FLASH_SR_BSY);
	if (FLASH->SR & FLASH_SR_EOP) {
		FLASH->SR = FLASH_SR_EOP;
	}
	/*start programming*/
	FLASH->CR |= FLASH_CR_PG;
	while(count>0)
	{
		/*write word*/
		*(volatile uint16_t*)(address) = *((uint16_t *)buff);
		/* check for errors */ 
		if (FLASH->SR  & (FLASH_SR_PGERR | FLASH_SR_PGERR))
		{
			FLASH->SR  |= FLASH_SR_PGERR | FLASH_SR_PGERR;
			FLASH->CR &= ~(FLASH_CR_PG);
			return 0; 
		}	
		
		/*next block*/
		address +=2;
		buff    +=2;
		count   -=2;
	}
	FLASH->CR &= ~(FLASH_CR_PG);
	return 1;
}
