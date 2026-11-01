#include "stm32f10x.h"                  // Device header
void LightSenser_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIOB_InitStructure;
	GPIOB_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIOB_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIOB_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init (GPIOB,&GPIOB_InitStructure);
}
uint8_t lightsenser_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}