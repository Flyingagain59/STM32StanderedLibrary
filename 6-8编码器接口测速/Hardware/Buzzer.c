#include "stm32f10x.h"                  // Device header

/**
  * @brief  蜂鸣器初始化函数
  * @param  无
  * @retval 无
  * @note   配置GPIOB的Pin12为推挽输出，初始状态为关闭（高电平）
  */
void Buzzer_Init (void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);    // 使能GPIOB外设时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;                    // 定义GPIO初始化结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        // 设置为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;              // 选择Pin12连接蜂鸣器
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       // 设置输出速度为50MHz
	GPIO_Init (GPIOB,&GPIO_InitStructure);                  // 应用配置到GPIOB
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);                       // 初始化后蜂鸣器引脚置高电平（蜂鸣器关闭，低电平开启）
}

/**
  * @brief  蜂鸣器开启
  * @param  无
  * @retval 无
  */
void Buzzer_ON ()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);                     // Pin12输出低电平，蜂鸣器鸣叫
}

/**
  * @brief  蜂鸣器关闭
  * @param  无
  * @retval 无
  */
void Buzzer_OFF ()
{
	GPIO_SetBits(GPIOB, GPIO_Pin_12);                       // Pin12输出高电平，蜂鸣器停止
}

/**
  * @brief  蜂鸣器状态翻转
  * @param  无
  * @retval 无
  * @note   读取当前引脚状态，若为开启则关闭，若为关闭则开启
  */
void Buzzer_Turn(void)
{
	// 读取Pin12的输入数据寄存器，判断当前状态
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == 0)     // 低电平表示当前蜂鸣器是开启状态
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);                   // 关闭蜂鸣器
	}
	else                                                    // 高电平表示当前蜂鸣器是关闭状态
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);                 // 开启蜂鸣器
	}
}
