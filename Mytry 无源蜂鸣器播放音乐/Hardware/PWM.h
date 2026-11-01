#include "stm32f10x.h"                  // Device header

#ifndef __PWM_H
#define __PWM_H

void PWM_Init(uint16_t ARR,uint16_t PSC,uint16_t CCR);
void PWM_SetCompare2(uint16_t Compare);     //仅改变占空比

#endif
