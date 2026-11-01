#ifndef _SERIAL_H_
#define _SERIAL_H_
#include <stdio.h>                      // 标准输入输出头文件

#include "stm32f10x.h"                  // 包含STM32标准库头文件

extern uint8_t serial_TxPacket[] ;
extern uint8_t serial_RxPacket[] ;
// 串口初始化函数声明
void Serial_Init(void);
// 串口发送一个字节函数声明
void Serial_SendByte(uint8_t byte);
// 串口发送数组函数声明
void Serial_SendArray(uint8_t *array, uint16_t length);
// 串口发送字符串函数声明
void Serial_SendString(char *str);
uint32_t Serial_Pow(uint32_t x, uint32_t y);
void Serial_SendNumber(uint32_t num ,uint32_t length);
void Serial_SendPacket(void);
uint8_t Serial_GetRxFlag();

#endif
