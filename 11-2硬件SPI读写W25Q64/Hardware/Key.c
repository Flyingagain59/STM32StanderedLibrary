#include "stm32f10x.h"                  // Device header
#include "delay.h"
void Key_Init ()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIOB_InitStructure;
	GPIOB_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIOB_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_11;
	GPIOB_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init (GPIOB,&GPIOB_InitStructure);
	
}
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
