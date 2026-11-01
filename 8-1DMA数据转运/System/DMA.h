#ifndef __DMA_H                           // 条件编译，防止头文件重复包含
#define __DMA_H

#include "stm32f10x.h"                    // 包含STM32标准库头文件

// 函数声明 --------------------------------------------------------------------
void MyDMA_Init(uint32_t AddrA ,uint32_t AddrB , uint16_t Size);  // DMA初始化函数声明
void MyDMA_Transfer(void);                                        // DMA数据传输函数声明

#endif                                    // 结束条件编译
