#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Key.h"
#include "AD.h"
#include "Motor.h"
#include "Encoder.h"
#include "serial.h"
#include "RP.h"

int main (void)
{

	OLED_Init();
	AD_Init();
	while (1)
	{
		OLED_Printf(0,0,OLED_8X16,"AD:%04d",AD_Getvalue());
		OLED_Update();
	}
}
void TIM1_UP_IRQHandler(void)
{
	static uint16_t cnt = 0;
	if (TIM_GetITStatus(TIM1 , TIM_IT_Update) == SET)
	{
		cnt++;
		Key_tick();

		if(cnt >= 40)
		{
			cnt = 0;
			
		}
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
	}
}
