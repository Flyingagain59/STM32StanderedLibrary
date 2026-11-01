#include "stm32f10x.h"                  // Device header
#include "Encode.h"
#include "OLED.h"

int16_t Num;

int main (void)
{
	Encode_Init();
	OLED_Init();
	OLED_ShowString(1,1,"Num:");
	while(1)
	{
		Num += Encode_Get();
		OLED_ShowSignedNum(1,5,Num,5);
	}
}

