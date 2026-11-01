#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Servo.h"
#include "Key.h"
#include "OLED.h"

float angle = 0;
uint8_t keyNumber = 0;
int main (void)
{
	Servo_Init();
	Key_Init();
	OLED_Init();
	OLED_ShowString(1, 1, "Angle:");
	while(1)
	{
		keyNumber = Key_GetNumber();
		if (keyNumber == 1)
		{
			angle += 30;
			if (angle > 180)
			{
				angle = 0;
			}
		}			
		Servo_SetAngle(angle);
		OLED_ShowNum(1, 7, angle, 3);
	}
}

