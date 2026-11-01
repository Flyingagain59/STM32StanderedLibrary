#ifndef HARDWARE_ENCODER_H
#define HARDWARE_ENCODER_H
#include "stm32f10x.h"                  // Device header
void Encoder_Init(void);
int16_t Encoder_GetCount(void);

#endif

