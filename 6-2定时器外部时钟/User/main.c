#include "stm32f10x.h"                  // Device header
#include "Timer.h"
#include "OLED.h"

uint16_t number;

int main (void)
{
	OLED_Init();
	Timer_Init();
	
	OLED_ShowString (1,1,"num: ");
	OLED_ShowString (2,1,"cnt: ");
	
	while(1)
	{

		
	}
}

