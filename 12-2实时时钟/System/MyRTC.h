#ifndef _RTC_H
#define _RTC_H
#include "stm32f10x.h"
extern uint16_t MyRTC_Time[];

void MyRTC_ReadTime(void);
void MyRTC_SetTime(void);
void MyRTC_Init(void);

#endif /* _RTC_H */
