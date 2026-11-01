#include "Store.h"
#include "MyFlash.h"

#define FLASH_ADR 0x0800fc00
#define STORE_SOUNT 512

uint16_t Store_Data[STORE_SOUNT];

void Store_Init(void)
{
    /***************************闪存初始化**************************/

    if (MyFLASH_ReadHalfWord(FLASH_ADR) != 0xa5a5)
    {
        MyFLASH_EreasePage(FLASH_ADR);
        MyFLASH_ProgramHalfWord(FLASH_ADR , 0xa5a5);
        for (uint16_t i = 1; i < 512; i++)                      //i从1开始而不是0，因为第一个数据是标志位
        {
            MyFLASH_ProgramHalfWord(FLASH_ADR + i*2 , 0x0000); //第一个参数是地址，第二个参数是要写入的数据0000
        }
    }
    /****************************把闪存的数据全部转存到SRAM数组中去***********************/
    for (uint16_t i = 0; i < 512; i++)                      //i从0开始而不是1，
    {
        Store_Data[i] = MyFLASH_ReadHalfWord(FLASH_ADR + i*2); 
    }
}
void Store_Save (void)
{
    MyFLASH_EreasePage(FLASH_ADR);
    for (uint16_t i = 0; i < 512; i++)                      
    {
        MyFLASH_ProgramHalfWord(FLASH_ADR + i*2 , Store_Data[i]); 
    }
}
void Store_Clear(void)
{
    for (uint16_t i = 1; i < 512; i++)                      //i从1开始而不是0，因为第一个数据是标志位
    {
        Store_Data[i] = 0x0000;
    }
    Store_Save();
}