#ifndef _STORE_H
#define _STORE_H

#include "stm32f10x.h"

extern uint16_t Store_Data[512];

void Store_Init(void);

void Store_Save (void);

void Store_Clear(void);
#endif
