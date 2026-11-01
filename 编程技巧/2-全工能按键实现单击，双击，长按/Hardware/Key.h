#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"                  // Device header


#define Key_count			            	 4
#define Key_1                                0
#define Key_2                                1
#define Key_3                                2
#define Key_4                                3

#define Key_Pressed                         1
#define Key_UnPressed                       0

#define Key_Hold   							0x01
#define Key_Down							0x02
#define Key_UP								0x04
#define Key_Single						    0x08
#define Key_Double						    0x10
#define Key_Long							0x20
#define Key_Repeat						    0x40

#define Key_Time_Double						200
#define Key_Time_Long						2000
#define Key_Time_Repeat						60

void Key_Init (void);
uint8_t Key_GetState (uint8_t n);
void Key_tick (void);
uint8_t Key_Check (uint8_t n ,uint8_t flag);


#endif
