#include "stm32f10x.h"                  // Device header
#include "delay.h"                         // Delay header

uint8_t Key_Number = 0;
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
	if (GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_1) == 0)
	{
		return 1;
	}
	else if (GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_11) == 0)
	{
		return 2;
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