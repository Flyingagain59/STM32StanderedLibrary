#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"                  // Device header

void Key_Init (void);
uint8_t Key_GetNumber (void);
uint8_t Key_GetState (void);
void Key_tick (void);
#endif
