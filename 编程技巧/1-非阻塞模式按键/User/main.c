#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Timer.h"
#include "Key.h"
#include "LED.h"
#include "delay.h"

uint8_t LED1Mode;
uint8_t LED2Mode;
uint8_t KeyNumber;
uint16_t i;
int main (void)
{
	OLED_Init();
	Timer_Init();
	Key_Init();
	LED_Init();
	while(1)
	{
		KeyNumber = Key_GetNumber();

		if (KeyNumber == 1)
		{
			LED1Mode ++;
			LED1Mode%=5;
			LED1_SetMode(LED1Mode);
		}if (KeyNumber == 2)
		{
			LED2Mode ++;
			LED2Mode%=5;
			LED2_SetMode(LED2Mode);
		}
		OLED_ShowNum(1 , 1 , i++ , 5);
		OLED_ShowNum(2 , 1 , LED1Mode , 1);
		OLED_ShowNum(3 , 1 , LED2Mode , 1);

	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2 , TIM_IT_Update) == SET)
	{
		Key_tick();
		LED1_Tick();
		LED2_Tick();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
