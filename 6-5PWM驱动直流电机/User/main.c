#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Motor.h"
#include "OLED.h"

int main (void)
{
	Motor_Init();
	OLED_Init();
	Motor_SetSpeed(20);
	while(1)
	{
		
	}
}


