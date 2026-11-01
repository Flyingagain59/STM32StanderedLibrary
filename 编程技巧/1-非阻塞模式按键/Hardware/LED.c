#include "stm32f10x.h"                  // Device header

uint16_t LED_count;
uint8_t LED1_MODE;
uint8_t LED2_MODE;
void LED_Init (void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init (GPIOA,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1|GPIO_Pin_2);
}
void LED1_ON ()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}
void LED1_OFF ()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

void LED2_ON ()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}
void LED2_OFF ()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

void LED1_Tick(void)
{
	if (LED1_MODE == 0)
	{
		LED1_OFF();
	}
	else if (LED1_MODE == 1)
	{
		LED1_ON();
	}
	else if (LED1_MODE == 2)
	{
		LED_count++;
		LED_count %=1000;
		if (LED_count < 500)
		{
			LED1_ON();
		}else{
		LED1_OFF();
		}
	}
	else if (LED1_MODE == 3)
	{
		LED_count++;
		LED_count %=100;
		if (LED_count < 50)
		{
			LED1_ON();
		}else{
		LED1_OFF();
		}
	}else if (LED1_MODE == 4)
	{
		LED_count++;
		LED_count %=1000;
		if (LED_count < 100)
		{
			LED1_ON();
		}else{
		LED1_OFF();
		}
	}
}
void LED1_SetMode (uint8_t mode)
{
	LED1_MODE = mode;
}
void LED2_Tick(void)
{
	if (LED2_MODE == 0)
	{
		LED2_OFF();
	}
	else if (LED2_MODE == 1)
	{
		LED2_ON();
	}
	else if (LED2_MODE == 2)
	{
		LED_count++;
		LED_count %=1000;
		if (LED_count < 500)
		{
			LED2_ON();
		}else{
		LED2_OFF();
		}
	}
	else if (LED2_MODE == 3)
	{
		LED_count++;
		LED_count %=100;
		if (LED_count < 50)
		{
			LED2_ON();
		}else{
		LED2_OFF();
		}
	}else if (LED2_MODE == 4)
	{
		LED_count++;
		LED_count %=1000;
		if (LED_count < 100)
		{
			LED2_ON();
		}else{
		LED2_OFF();
		}
	}
}
void LED2_SetMode (uint8_t mode)
{
	LED2_MODE = mode;
}