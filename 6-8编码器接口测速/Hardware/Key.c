#include "stm32f10x.h"                  // Device header
#include "delay.h"                      // 延时函数头文件

/**
  * @brief  按键初始化函数
  * @param  无
  * @retval 无
  * @note   配置GPIOB的Pin1和Pin11为上拉输入模式，连接独立按键
  */
void Key_Init ()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);    // 使能GPIOB外设时钟
	
	GPIO_InitTypeDef GPIOB_InitStructure;                   // 定义GPIO初始化结构体变量
	GPIOB_InitStructure.GPIO_Mode=GPIO_Mode_IPU;            // 设置为上拉输入模式（按键松开时为高电平）
	GPIOB_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_11;    // 选择Pin1和Pin11（同时配置两个引脚）
	GPIOB_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;        // 设置输出速度（输入模式下此参数无效，但需赋值）
	GPIO_Init (GPIOB,&GPIOB_InitStructure);                 // 调用GPIO_Init函数应用配置
	
}

/**
  * @brief  获取按键编号
  * @param  无
  * @retval 返回按键编号：0-无按键按下，1-按键1按下，2-按键2按下
  * @note   采用软件消抖处理，等待按键释放后才返回键值
  */
uint8_t Key_GetNumber ()
{
	uint8_t keynum =0;                                      // 初始化按键编号为0（表示无按键）
	
	// 检测按键1（连接在GPIOB_Pin1）
	if ( GPIO_ReadInputDataBit (GPIOB,GPIO_Pin_1) == 0)     // 读取Pin1电平，低电平表示按键按下
	{
		Delay_ms (20);                                      // 延时20ms进行软件消抖，过滤机械抖动
		while(GPIO_ReadInputDataBit (GPIOB,GPIO_Pin_1) == 0);// 等待按键释放，阻塞直到引脚变为高电平
		Delay_ms (20);                                      // 释放后再延时20ms消抖
		keynum =1;                                          // 设置返回值为按键1
	}
	
	// 检测按键2（连接在GPIOB_Pin11）
	if ( GPIO_ReadInputDataBit (GPIOB,GPIO_Pin_11) == 0)    // 读取Pin11电平，低电平表示按键按下
	{
		Delay_ms (20);                                      // 延时20ms进行软件消抖
		while(GPIO_ReadInputDataBit (GPIOB,GPIO_Pin_11) == 0);// 等待按键释放
		Delay_ms (20);                                      // 释放后再延时20ms消抖
		keynum =2;                                          // 设置返回值为按键2
	}
	
	return keynum;                                          // 返回检测到的按键编号
}
