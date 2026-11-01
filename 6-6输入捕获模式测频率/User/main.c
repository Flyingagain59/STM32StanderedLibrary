#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"
#include "OLED.h"
#include "InputCapture.h"
int main (void)
{
	/* 初始化OLED显示屏 */
	OLED_Init();
	/* OLED显示频率信息 */
	OLED_ShowString(1, 1, "Freq:");
	/* 初始化PWM (TIM2 CH1, PA0, 1kHz) */
	PWM_Init();
	PWM_SetPrescaler(720-1);
	PWM_SetCompare1(50);				// 设置50%占空比，产生明显的上升沿

	/* 初始化输入捕获 (TIM3 CH1, PA6) */
	IC_Init();

	while(1)
	{
		/* 获取测得的频率值并显示在OLED上 */
		OLED_ShowNum(1, 7, IC_GetFrequency(), 8);
	}
}

