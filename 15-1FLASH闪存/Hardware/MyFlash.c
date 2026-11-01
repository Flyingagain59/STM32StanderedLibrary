#include "MyFlash.h"

uint32_t MyFLASH_ReadWord(uint32_t addr)
{
    return *((__IO uint32_t*)(addr));   
}
uint16_t MyFLASH_ReadHalfWord(uint32_t addr)
{
	return *((__IO uint16_t*)(addr));   
}
uint8_t MyFLASH_ReadByte(uint32_t addr)
{
	return *((__IO uint8_t*)(addr));   
}

void MyFLASH_EreaseAllPage(void)
{
    FLASH_Unlock();
    FLASH_EraseAllPages();
    FLASH_Lock();
}

void MyFLASH_EreasePage(uint32_t page)
{
    FLASH_Unlock();
    FLASH_ErasePage(page);
    FLASH_Lock();
}
void MyFLASH_ProgramWord(uint32_t addr, uint32_t Data)
{
    FLASH_Unlock();
    FLASH_ProgramWord(addr,Data);
    FLASH_Lock();
}
void MyFLASH_ProgramHalfWord(uint32_t addr, uint16_t Data)
{
    FLASH_Unlock();
    FLASH_ProgramHalfWord(addr,Data);
    FLASH_Lock();    
}