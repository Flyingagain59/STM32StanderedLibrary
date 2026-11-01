#include "stm32f10x.h"                  // Device header

/**
  * @brief  LED初始化函数
  * @param  无
  * @retval 无
  * @note   配置GPIOA的Pin1和Pin2为推挽输出，初始状态为熄灭（高电平）
  */
void LED_Init (void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    // 使能GPIOA外设时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;                    // 定义GPIO初始化结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        // 设置为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;    // 选择Pin1和Pin2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       // 设置输出速度为50MHz
	GPIO_Init (GPIOA,&GPIO_InitStructure);                  // 应用配置到GPIOA
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1|GPIO_Pin_2);             // 初始化后将两个LED引脚置高电平（LED熄灭，低电平点亮）
}

/**
  * @brief  LED1点亮
  * @param  无
  * @retval 无
  */
void LED1_ON ()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);                       // Pin1输出低电平，LED1点亮
}

/**
  * @brief  LED1熄灭
  * @param  无
  * @retval 无
  */
void LED1_OFF ()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);                         // Pin1输出高电平，LED1熄灭
}

/**
  * @brief  LED1状态翻转
  * @param  无
  * @retval 无
  * @note   读取当前引脚状态，若为点亮则熄灭，若为熄灭则点亮
  */
void LED1_Turn(void)
{
	// 读取Pin1的输入数据寄存器，判断当前状态
	if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0)       // 低电平表示当前LED1是点亮状态
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_1);                     // 熄灭LED1
	}
	else                                                    // 高电平表示当前LED1是熄灭状态
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);                   // 点亮LED1
	}
}

/**
  * @brief  LED2点亮
  * @param  无
  * @retval 无
  */
void LED2_ON ()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);                       // Pin2输出低电平，LED2点亮
}

/**
  * @brief  LED2熄灭
  * @param  无
  * @retval 无
  */
void LED2_OFF ()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);                         // Pin2输出高电平，LED2熄灭
}

/**
  * @brief  LED2状态翻转
  * @param  无
  * @retval 无
  * @note   读取当前引脚状态，若为点亮则熄灭，若为熄灭则点亮
  */
void LED2_Turn(void)
{
	// 读取Pin2的输入数据寄存器，判断当前状态
	if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2) == 0)       // 低电平表示当前LED2是点亮状态
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);                     // 熄灭LED2
	}
	else                                                    // 高电平表示当前LED2是熄灭状态
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);                   // 点亮LED2
	}
}
