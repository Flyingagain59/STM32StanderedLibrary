#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"                  // Device header

void Key_Init ();
uint8_t Key_GetNumber ();
uint8_t Key_GetState (void);
void Key_tick (void);
#endif
