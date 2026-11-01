#include "W25Q64.h"

void W25Q64_Init(void)
{
	MySPI_Init();
}

void W25Q64_ReadID(uint8_t *MID , uint16_t *DID )
{
    MySPI_Start();
    MySPI_SwapByte(W25Q64_JEDEC_ID);
    *MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    *DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    *DID <<=8;
    *DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    MySPI_Stop();
}
void W25Q64_WriteEnable(void)
{
    MySPI_Start();
    MySPI_SwapByte(W25Q64_WRITE_ENABLE);
    MySPI_Stop();
}
void W25Q64_WaitBusy(void)
{
    uint32_t timeout = 100000;
    MySPI_Start();
    MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
    while (MySPI_SwapByte(W25Q64_DUMMY_BYTE)&0x01 == 0x01 )
    {
        if (timeout-- == 0)
        {
            break;
        }
    }
    MySPI_Stop();
}
void W25Q64_PageProgram(uint32_t addr, uint8_t *data, uint16_t len)
{
    W25Q64_WriteEnable();
    MySPI_Start();
    MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
    MySPI_SwapByte((addr >> 16) & 0xFF);
    MySPI_SwapByte((addr >> 8) & 0xFF);
    MySPI_SwapByte(addr & 0xFF);
    for (int i = 0; i < len; i++)
    {
        MySPI_SwapByte(data[i]);
    }
    MySPI_Stop();
    W25Q64_WaitBusy();
    
}
void W25Q64_SectorErase(uint32_t addr)
{
    void W25Q64_WriteEnable(void);
    MySPI_Start();
    MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
    MySPI_SwapByte((addr >> 16) & 0xFF);
    MySPI_SwapByte((addr >> 8) & 0xFF);
    MySPI_SwapByte(addr & 0xFF);
    MySPI_Stop();
    W25Q64_WaitBusy();
}
void W25Q64_ReadData(uint32_t addr, uint8_t *data, uint32_t len)
{
    W25Q64_WriteEnable();
    MySPI_Start();
    MySPI_SwapByte(W25Q64_READ_DATA);
    MySPI_SwapByte((addr >> 16) & 0xFF);
    MySPI_SwapByte((addr >> 8) & 0xFF);
    MySPI_SwapByte(addr & 0xFF);
    for (int i = 0; i < len; i++)
    {
        data[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    }
    MySPI_Stop();
}
