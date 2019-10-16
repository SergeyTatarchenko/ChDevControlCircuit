/*************************************************
* File Name          : flash.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : flash.c header
*************************************************/
#ifndef FLASH_H
#define FLASH_H

#define STM32F1

#ifdef STM32F1
#include <stm32f10x.h>
#include "system_stm32f10x.h"
#endif

#define FLASH_ACCESS_WORD0	(uint32_t)0x45670123
#define FLASH_ACCESS_WORD1	(uint32_t)0xCDEF89AB

#define FLASH_START_ADRESS	(uint32_t)0x08000000
#define FLASH_PAGE_SIZE		(uint32_t)0x3FF


/*-----------------------------------------------*/
void flash_unlock(void);
void flash_lock(void);
int flash_write_page(uint8_t* data, uint32_t address, uint32_t count);
void flash_erase_page(uint32_t adress);

#endif
