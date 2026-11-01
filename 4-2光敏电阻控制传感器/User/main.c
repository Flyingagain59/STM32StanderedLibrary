#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"
#include "LED.h"

uint8_t KeyNum;

int main (void)
{
	Key_Init();
	LED_Init();
	while(1)
	{
		KeyNum = Key_GetNumber();
		if (KeyNum == 1)
		{
			LED1_Turn();
		}
		if (KeyNum == 2)
		{
			LED2_Turn();
		}
	}
}

