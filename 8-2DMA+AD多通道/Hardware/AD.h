#ifndef HARDWARE_AD_H
#define HARDWARE_AD_H
#include "stm32f10x.h"                  // Device header

void AD_Init(void);
void AD_Getvalue(void);

extern uint16_t AD_Value[4];  // 定义一个数组用于存储ADC转换结果，长度为4


#endif

