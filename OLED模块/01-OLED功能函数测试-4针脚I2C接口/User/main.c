#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "OLED_Data.h"
int main(void)
{
	/*OLED初始化*/
	OLED_Init();

	OLED_ShowString(0,0,"哈喽，世界。",OLED_8X16);

	OLED_Update();

	while (1)
	{
		
	}
}
