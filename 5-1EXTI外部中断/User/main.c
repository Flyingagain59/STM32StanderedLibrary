#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSeneor.h"

int main (void)
{
	OLED_Init();
	Count_Sensor_Init();
	OLED_ShowString (1,3,"Count:");
	while(1)
	{
		OLED_ShowNum (1,7,CountSensor_Count(),5);
	}
}

