#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Timer.h"
#include "Key.h"
#include "delay.h"

uint16_t Num1,Num2;
int main (void)
{
	OLED_Init();
	Timer_Init();
	Key_Init();

	OLED_ShowString(1,1,"Num1:");
	OLED_ShowString(2,1,"Num2:");

	while(1)
	{
		/*示例一
		if(Key_Check(Key_Hold))
		{
			Num1 = 1;
		}else {
			Num1 = 0;
		}*/

		/*示例二
		if(Key_Check (Key_Down))
		{
			Num1++;
		}else if(Key_Check (Key_UP))
		{
			Num2++;
		}

		OLED_ShowNum(1,6,Num1,5);
		OLED_ShowNum(2,6,Num2,5);*/

		/*示例三
		if (Key_Check(Key_Single))
		{
			Num1++;
		}
		if (Key_Check(Key_Double))
		{
			Num1 += 100;
		}if(Key_Check(Key_Long))
		{
			Num1 = 0;
		}*/

		//示例四
		if(Key_Check(Key_1,Key_Single)||Key_Check(0,Key_Repeat))
		{
			Num1++;
		}if(Key_Check(Key_2,Key_Single)||Key_Check(1,Key_Repeat))
		{
			Num1--;
		}
		if(Key_Check(Key_3,Key_Single))
		{
			Num1 = 0;
		}
		if(Key_Check(Key_4,Key_Long))
		{
			Num1 = 9999;
		}
		OLED_ShowNum(1,6,Num1,5);
		OLED_ShowNum(2,6,Num2,5);
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2 , TIM_IT_Update) == SET)
	{
		Key_tick();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
