#include "stm32f10x.h"                  // Device header

/**
  * @brief  蜂鸣器初始化
  * @param  无
  * @retval 无
  */
void Buzzer_Init (void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOB,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

/**
  * @brief  蜂鸣器响
  * @param  无
  * @retval 无
  */
void Buzzer_ON ()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

/**
  * @brief  蜂鸣器关闭
  * @param  无
  * @retval 无
  */
void Buzzer_OFF ()
{
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

/**
  * @brief  蜂鸣器翻转
  * @param  无
  * @retval 无
  */
void Buzzer_Turn(void)
{
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	}
}
