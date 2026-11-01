#ifndef _MYFLASH_H
#define _MYFLASH_H
#include "stm32f10x.h"

uint32_t MyFLASH_ReadWord(uint32_t addr);

uint16_t MyFLASH_ReadHalfWord(uint32_t addr);

uint8_t MyFLASH_ReadByte(uint32_t addr);

void MyFLASH_EreaseAllPage(void);

void MyFLASH_EreasePage(uint32_t page);

void MyFLASH_ProgramWord(uint32_t addr, uint32_t Data);

void MyFLASH_ProgramHalfWord(uint32_t addr, uint16_t Data);

#endif 
