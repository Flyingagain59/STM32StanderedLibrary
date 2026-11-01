#include "stm32f10x.h"                  // 设备头文件，包含STM32寄存器定义
#include "Delay.h"                      // 延时函数头文件
#include "OLED.h"                       // OLED显示屏驱动头文件
#include "Serial.h"                     // 串口驱动头文件

/**
  * @brief  主函数，程序入口
  * @param  无
  * @retval 无
  */
int main (void)
{
	// 初始化OLED显示屏
	OLED_Init();
	// 初始化串口，配置波特率9600，8位数据位，1位停止位，无校验
	Serial_Init();

//	uint8_t MyArray[10] = { 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B };
//	Serial_SendArray(MyArray, 10);
//	Serial_SendString("Hello, World!");
//	Serial_SendNumber (12345,5);

	printf("Number: %d\r\n",666);
	while(1)
	{
		
	}
}
