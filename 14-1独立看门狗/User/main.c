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
	OLED_Init();	// 初始化OLED显示屏
	Key_Init();		// 初始化按键

	OLED_ShowString(1,1,"IWDG Test");	// 显示标题

	// 检查是否是独立看门狗复位
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET)
	{
		OLED_ShowString(2,1,"IWDG Reset");	// 显示看门狗复位信息
		Delay_ms(500);
		OLED_ShowString(2,1,"            ");	// 清除显示
		Delay_ms(100);
		RCC_ClearFlag();	// 清除复位标志
	}else{
		OLED_ShowString(3,1,"Reset");	// 显示普通复位信息
		Delay_ms(500);
		OLED_ShowString(3,1,"            ");	// 清除显示
		Delay_ms(100);
		RCC_ClearFlag();	// 清除复位标志
	}

	// 独立看门狗初始化配置
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	// 使能写寄存器操作
	IWDG_SetPrescaler(IWDG_Prescaler_16);			// 设置预分频系数为16
	IWDG_SetReload(2499);							// 设置重载值，超时时间约1000ms
	IWDG_ReloadCounter();							// 喂狗，重装载计数器
	IWDG_Enable();									// 启动独立看门狗


	while(1)
	{
		Key_GetNumber();								// 读取按键值，如果有按键按下，则返回非0值（按键编号+1

		IWDG_ReloadCounter();							// 喂狗，重装载计数器
		OLED_ShowString(4,1,"feed");					// 显示按键信息
		Delay_ms(200);									// 延时200ms，超过看门狗超时时间，触发复位
		OLED_ShowString(4,1,"            ");			// 清除显示
		Delay_ms(600);									// 延时600ms
		
	}
}

