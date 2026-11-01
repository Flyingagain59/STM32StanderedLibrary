#include "stm32f10x.h"                  // Device header

/**
  * @brief  光敏传感器初始化
  * @param  无
  * @retval 无
  */
void LightSenser_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIOB_InitStructure;
	GPIOB_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIOB_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIOB_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init (GPIOB,&GPIOB_InitStructure);
}

/**
  * @brief  获取光敏传感器状态
  * @param  无
  * @retval 光敏传感器状态，0表示有光照，1表示无光照
  */
uint8_t lightsenser_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}