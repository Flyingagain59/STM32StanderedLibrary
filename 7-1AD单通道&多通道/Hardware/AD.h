#ifndef HARDWARE_AD_H
#define HARDWARE_AD_H
#include "stm32f10x.h"                  // Device header

void AD_Init(void);
uint16_t AD_Getvalue(uint8_t channel);

#endif
