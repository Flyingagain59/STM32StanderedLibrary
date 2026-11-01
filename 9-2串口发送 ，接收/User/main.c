#include "stm32f10x.h"                  // 设备头文件，包含STM32寄存器定义
#include "Delay.h"                      // 延时函数头文件
#include "OLED.h"                       // OLED显示屏驱动头文件
#include "Serial.h"                     // 串口驱动头文件

uint8_t RxData;

/**
  * @brief  主函数，程序入口
  * @param  无
  * @retval 无
  */
int main (void)
{
	// 初始化OLED显示屏
	OLED_Init();
	OLED_ShowString(1, 1, "RXdata:");

	// 初始化串口，配置波特率9600，8位数据位，1位停止位，无校验
	Serial_Init();

	while(1)
	{
		if (Serial_GetRxFlag() == 1)
		{
			RxData = Serial_GetRxData();
			Serial_SendByte(RxData);
			OLED_ShowHexNum(1, 8, RxData,2);
		}
		
	}
}
