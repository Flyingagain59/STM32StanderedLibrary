#include "stm32f10x.h"                  // Device header
#include "delay.h"

/**
  * @brief  按键初始化
  * @param  无
  * @retval 无
  */
void Key_Init ()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIOB_InitStructure;
	GPIOB_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIOB_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_11;
	GPIOB_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init (GPIOB,&GPIOB_InitStructure);
	
}

/**
  * @brief  获取按键键值
  * @param  无
  * @retval 键值，1表示KEY1按下，2表示KEY2按下，0表示无按键按下
  */
uint8_t Key_GetNumber ()
{
	uint8_t keynum =0;
	if ( GPIO_ReadInputDataBit (GPIOB,GPIO_Pin_1) == 0)
	{
		Delay_ms (20);
		while(GPIO_ReadInputDataBit (GPIOB,GPIO_Pin_1) == 0);
		Delay_ms (20);
		keynum =1;
	}
	if ( GPIO_ReadInputDataBit (GPIOB,GPIO_Pin_11) == 0)
	{
		Delay_ms (20);
		while(GPIO_ReadInputDataBit (GPIOB,GPIO_Pin_11) == 0);
		Delay_ms (20);
		keynum =2;
	}
	return keynum;
}
