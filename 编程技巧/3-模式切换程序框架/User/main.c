#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Timer.h"

uint8_t CurrentMode,NextMode = 1;
uint8_t KEY_Number = 0;
uint8_t count = 0;
//模式一
void Mode1_Init()
{
	OLED_Clear();
	OLED_ShowString(1, 1, "[Mode1]");

}
void Mode1_Loop()
{
	KEY_Number = Key_GetNumber();
	if (KEY_Number == 1)
	{
		NextMode = 2;
	}
	if (KEY_Number == 2)
	{
		LED1_Turn();
	}
	
}
void Mode1_Exit()
{
	LED1_OFF();
}

//模式二
void Mode2_Init()
{
	OLED_Clear();
	OLED_ShowString(1, 1, "[Mode2]");
	OLED_ShowString(2, 1, "Count:");
	OLED_ShowNum(2, 7, count,3);
}
void Mode2_Loop()
{
	KEY_Number = Key_GetNumber();
	if (KEY_Number == 1)
	{
		NextMode = 3;
	}
	if (KEY_Number == 2)
	{
		count++;
		OLED_ShowNum(2, 7, count,3);
	}
}
void Mode2_Exit()
{
	count = 0;
}

//模式三
uint8_t Timer = 0;
uint8_t TimerRunFlag = 0;
void Mode3_Init()
{
	OLED_Clear();
	OLED_ShowString(1, 1, "[Mode3]");
	OLED_ShowString(2, 1, "Time:");
	OLED_ShowNum(2, 6, Timer,3);
}
void Mode3_Loop()
{
	KEY_Number = Key_GetNumber();
	if (KEY_Number == 1)
	{
		NextMode = 1;
	}
	if (KEY_Number == 2)
	{
		TimerRunFlag =!TimerRunFlag;
	}
	OLED_ShowNum(2, 6, Timer,3);

}
void Mode3_Exit()
{
	TimerRunFlag = 0;
	Timer = 0;
}
void Mode3_Tick()
{
	static uint16_t TimerCount = 0;
	TimerCount++;
	if (TimerCount >= 1000)
	{
		TimerCount = 0;
		if (TimerRunFlag)
		{
			Timer++;
		}
		
	}

}
int main (void)
{
	OLED_Init();
	LED_Init();
	Key_Init();
	Timer_Init();

	while(1)
	{
		if (CurrentMode == NextMode)
		{
			switch (CurrentMode)
			{
				case 1:
					Mode1_Loop();
					break;
				case 2:
					Mode2_Loop();
					break;
				case 3:
					Mode3_Loop();
					break;	
			}
			
		}else{
			switch (CurrentMode)
			{
				case 1:
					Mode1_Exit();
					break;
				case 2:
					Mode2_Exit();
					break;
				case 3:
					Mode3_Exit();
					break;
			}
			switch (NextMode)
			{
				case 1:
					Mode1_Init();
					break;
				case 2:
					Mode2_Init();
					break;
				case 3:
					Mode3_Init();
					break;
			}
			CurrentMode = NextMode;
		}
	}
}
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2 , TIM_IT_Update) == SET)
	{
		if (CurrentMode == NextMode)
		{
			switch (CurrentMode)
			{
				case 3:
					Mode3_Tick();
					break;
			}
		}	
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

