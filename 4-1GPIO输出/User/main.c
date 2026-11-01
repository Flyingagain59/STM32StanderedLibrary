#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
uint8_t Keynum;
int main (void)
{
	LED_Init();
	Key_Init();
	
	while(1)
	{
		Keynum=Key_GetNumber();
		if(Keynum==1)
		{
			LED1_Turn();
		}
		if(Keynum==2)
		{
			LED2_Turn();
		}
	}
}

