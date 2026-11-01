#include "stm32f10x.h"                  // Device header
#include "delay.h"                         // Delay header

uint8_t Key_Number = 0;
void Key_Init ()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init (GPIOB,&GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_11;
	GPIO_Init (GPIOA,&GPIO_InitStructure);	
}
uint8_t Key_GetNumber ()
{
	uint8_t temp ;
	if (Key_Number)
	{
		temp = Key_Number;
		Key_Number = 0;
		return temp;
	}
	return 0;
}
uint8_t Key_GetState (void)
{
	if (GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_10) == 0)
	{
		return 1;
	}
	else if (GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_11) == 0)
	{
		return 2;
	}else if (GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_11) == 0)
	{
		return 3;
	}else if (GPIO_ReadInputDataBit(GPIOA , GPIO_Pin_12) == 0)
	{
		return 4;
	}
	else
	{
		return 0;
	}
	
}
void Key_tick (void)
{
	static uint8_t count = 0;
	static uint8_t CurrentState , PrevState;
	count ++;
	if(count >=20)
	{
		count = 0;
		PrevState = CurrentState;
		CurrentState = Key_GetState();
		if (CurrentState == 0&&PrevState !=0)
		{
			Key_Number = PrevState;
		}
	}
}