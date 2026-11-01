#include "stm32f10x.h"                  // Device header

/**
  * @brief  光敏传感器初始化函数
  * @param  无
  * @retval 无
  * @note   配置GPIOB的Pin13为上拉输入模式，用于读取光敏传感器状态
  */
void LightSenser_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);    // 使能GPIOB外设时钟
	
	GPIO_InitTypeDef GPIOB_InitStructure;                   // 定义GPIO初始化结构体
	GPIOB_InitStructure.GPIO_Mode=GPIO_Mode_IPU;            // 设置为上拉输入模式
	GPIOB_InitStructure.GPIO_Pin=GPIO_Pin_13;               // 选择Pin13连接光敏传感器
	GPIOB_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;        // 设置引脚速度（输入模式下此参数无效）
	GPIO_Init (GPIOB,&GPIOB_InitStructure);                 // 应用配置到GPIOB
}

/**
  * @brief  获取光敏传感器状态
  * @param  无
  * @retval Bit_SET(1)或Bit_RESET(0)，根据光线强度返回不同电平
  * @note   读取GPIOB_Pin13的电平状态，判断环境光线情况
  */
uint8_t lightsenser_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);        // 读取Pin13的输入电平并返回
}