#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main (void)
{
	OLED_Init();											// 初始化OLED显示屏
	Key_Init();												// 初始化按键

	OLED_ShowString(1,1,"WWDG Test");						// 显示标题

	// 检查是否是独立看门狗复位
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET)
	{
		OLED_ShowString(2,1,"WWDG Reset");					// 显示看门狗复位信息
		Delay_ms(500);
		OLED_ShowString(2,1,"            ");				// 清除显示
		Delay_ms(100);
		RCC_ClearFlag();									// 清除复位标志
	}else{
		OLED_ShowString(3,1,"Reset");						// 显示普通复位信息
		Delay_ms(500);
		OLED_ShowString(3,1,"            ");				// 清除显示
		Delay_ms(100);
		RCC_ClearFlag();									// 清除复位标志
	}

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);	// 使能独立看门狗时钟
	WWDG_SetPrescaler(WWDG_Prescaler_8);					// 设置分频系数为8
	WWDG_SetWindowValue(21 |0x40);							// 设置窗口值
	WWDG_Enable(54 |0x40);									// 设置计数器值，并启动看门狗
	WWDG_EnableIT();										// 开启中断




	while(1)
	{
		Key_GetNumber();								// 读取按键值，如果有按键按下，则返回非0值（按键编号+1
		OLED_ShowString(4,1,"feed");					// 显示按键信息
		Delay_ms(20);									// 延时200ms，超过看门狗超时时间，触发复位
		OLED_ShowString(4,1,"    ");			// 清除显示
		Delay_ms(20);									// 延时600ms
		WWDG_SetCounter(0x40 |54);							// 重置看门狗计数器，防止复位发生

	}
}

