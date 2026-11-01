#include "stm32f10x.h"                  // Device header
#include "delay.h"                         // Delay header
#include "key.h"                           // Key header


uint8_t Key_flag[Key_count] ;

void Key_Init (void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIOB_InitStructure;
	GPIOB_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIOB_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_11;
	GPIOB_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init (GPIOB,&GPIOB_InitStructure);

	GPIOB_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIOB_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_15;
	GPIOB_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init (GPIOB,&GPIOB_InitStructure);
	
}
uint8_t Key_GetState (uint8_t  n)
{
	if(n == 0)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
		{
			return Key_Pressed;
		}
	}
	else if(n == 1)
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)
		{
			return Key_Pressed;
		}
	}	
	else if(n == 2)
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) == 1)
		{
			return Key_Pressed;
		}
	}else if(n == 3)
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) == 1)
		{
			return Key_Pressed;
		}
	}
	return Key_UnPressed;	
}

uint8_t Key_Check (uint8_t n ,uint8_t flag)
{
	if (Key_flag[n] & flag)
	{
		if (flag != Key_Hold)
		{
			Key_flag[n] &= ~flag;
		}
		return 1;
	}
	else
	{
		return 0;
	}
}


void Key_tick (void)
{
	static uint8_t count = 0,i;
	static uint8_t CurrentState[Key_count] , PrevState[Key_count];
	static uint8_t s[Key_count] ;
	static uint16_t time[Key_count];

	for (i = 0; i < Key_count; i ++)
	{
		if (time[i] > 0)
		{
			time[i]--;
		}
	}

	count ++;
	if(count >=20)
	{
		for (i = 0; i < Key_count; i ++)
		{
			count = 0;
			PrevState[i] = CurrentState[i];
			CurrentState[i] = Key_GetState(i);
			if (CurrentState[i] == Key_Pressed)
			{
				//hold = 1;
				Key_flag[i] |= Key_Hold;
			}else{
				//hold = 0;
				Key_flag[i] &= ~Key_Hold;
			}

			if (PrevState[i] == Key_UnPressed && CurrentState[i] == Key_Pressed)
			{
				//pressed 
				Key_flag[i] |= Key_Down;
			}

			if (PrevState[i] == Key_Pressed && CurrentState[i] == Key_UnPressed)
			{
				//released 
				Key_flag[i] |= Key_UP;
			}

			switch (s[i])
			{
				case 0:
					if(CurrentState[i] == Key_Pressed)
					{
						time[i] = Key_Time_Long;
						s[i] = 1;
					}
					break;
				case 1:
					if(CurrentState[i] == Key_UnPressed)
					{
						time[i] = Key_Time_Double;
						s[i] = 2;
					}
					else if (time[i] == 0)
					{
						//long = 1
						Key_flag[i] |= Key_Long;
						time[i] = Key_Time_Repeat;
						s[i] = 4;
					}
					break;
				case 2:
					if (CurrentState[i] == Key_Pressed)
					{
						//double = 1
						Key_flag[i] |= Key_Double;
						s[i] = 3;
					}
					else if (time[i] == 0)
					{
						//single = 1
						Key_flag[i] |= Key_Single;
						s[i] = 0;
					}
					break;
				case 3:
					if (CurrentState[i] == Key_UnPressed)
					{
						s[i] = 0;
					}
					break;
				case 4:
					if (CurrentState[i] == Key_UnPressed)
					{
						s[i] = 0;
					}else if (time[i] == 0)
					{
						Key_flag[i] |=Key_Repeat;
						time[i] = 100;
						s[i] = 4;
					}
					break;
			}
		}
	}
}
		
	