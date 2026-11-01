#include "stm32f10x.h"                  // Device header
#include "Key.h"
#include "OLED.h"
#include "Delay.h"

uint16_t ArrayWrite[] = {0x1234, 0x5678};
uint16_t ArrayRead[2];
uint8_t KeyNumber;

int main (void)
{
	OLED_Init();
	Key_Init();

	OLED_ShowString(1,1,"W:");
	OLED_ShowString(2,1,"R:");

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	// 使能定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);	// 使能备份寄存器时钟

	PWR_BackupAccessCmd(ENABLE);		// 允许访问备份寄存器

//	BKP_WriteBackupRegister(BKP_DR1, 0x1234);	// 向备份寄存器写入数据
//	OLED_ShowHexNum(1,1,BKP_ReadBackupRegister(BKP_DR1),4);		// 从备份寄存器读取数据

	while(1)
	{
		KeyNumber = Key_GetNumber();	// 读取按键值
		if(KeyNumber == 1)	// 按下按键
		{
			ArrayWrite[0]++;	// 按键按下，数据加1
			ArrayWrite[1]++;	// 按键按下，数据加1
			BKP_WriteBackupRegister(BKP_DR1, ArrayWrite[0]);	// 向备份寄存器写入数据
			BKP_WriteBackupRegister(BKP_DR2, ArrayWrite[1]);	// 向备份寄存器写入数据
			OLED_ShowHexNum(1,3,ArrayWrite[0],4);		
			OLED_ShowHexNum(1,8,ArrayWrite[1],4);		
		}
		ArrayRead[0] = BKP_ReadBackupRegister(BKP_DR1);	// 从备份寄存器读取数据
		ArrayRead[1] = BKP_ReadBackupRegister(BKP_DR2);	// 从备份寄存器读取数据
		OLED_ShowHexNum(2,3,ArrayRead[0],4);		
		OLED_ShowHexNum(2,8,ArrayRead[1],4);		
	}
}

