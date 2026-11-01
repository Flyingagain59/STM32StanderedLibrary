#include "MySPI.h"


void MySPI_W_SS(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);
}

void MySPI_W_SCK(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);
}

void MySPI_W_MOSI(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);
}

uint8_t MySPI_W_MISO(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}
void MySPI_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    MySPI_W_SS(1);
    MySPI_W_SCK(0);
}
void MySPI_Start(void)
{
    MySPI_W_SS(0);
}
void MySPI_Stop(void)
{
    MySPI_W_SS(1);
}
uint8_t MySPI_SwapByte(uint8_t Byte)
{
    uint8_t i;
    for (i = 0; i < 8; i++) 
    {
        MySPI_W_MOSI(Byte & 0x80);
        Byte <<= 1;
        MySPI_W_SCK(1);
        if (MySPI_W_MISO())
        {
            Byte |= 0x01;
        }
        MySPI_W_SCK(0);
    }
    return Byte;
}
