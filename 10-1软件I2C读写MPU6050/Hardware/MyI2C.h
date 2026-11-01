#ifndef _My_IIC_H
#define _My_IIC_H

#include "stm32f10x.h"
#include "Delay.h"

void My_IIC_W_SCL(uint8_t BitValue);

void My_IIC_W_SDA(uint8_t BitValue);

uint8_t My_IIC_Read (void);

void My_IIC_Init (void);

void My_IIC_Start(void);

void My_IIC_Stop(void);

void My_IIC_SendByte(uint8_t Byte);

uint8_t My_IIC_ReceiveByte(void);

void My_IIC_SendAck(uint8_t Ackbit);

uint8_t My_IIC_ReceiveAck(void);
#endif 
