#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

int main (void)
{
	OLED_Init();
	OLED_ShowChar (1 ,1 ,'A');
	OLED_ShowString (1,3,"zzq");
	OLED_ShowNum (2,3,11111,5);
	OLED_ShowSignedNum (3,1,-666,3);
	OLED_ShowHexNum (4 ,1,0x1111,4);
	OLED_ShowBinNum (4,1,0x1111,16);
	OLED_Clear ();
	while(1)
	{
		
	}
}

