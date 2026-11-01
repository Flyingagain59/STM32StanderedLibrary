#include "stm32f10x.h"

/**
 * @brief  初始化TIM3输入捕获模式
 * @note   使用TIM3_CH1 (PA6) 作为输入捕获引脚
 *         从模式复位: TI1FP1上升沿触发，捕获CNT值到CCR1后自动清零CNT
 *         定时器时钟配置: PSC=72-1，计数频率1MHz
 *         频率计算公式: Frequency = 1,000,000 / CCR1
 *
 *         硬件接线: PA0 (PWM输出) 跳线连接 PA6 (输入捕获)
 */
void IC_Init(void)
{
	/* 使能TIM3和GPIOA时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* 配置PA6为浮空输入 (TIM3_CH1默认引脚) */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* 配置TIM3时基 */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65535;			/* 16位最大自动重装值 */
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;		/* 72MHz / 72 = 1MHz */
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

	/* 配置输入捕获通道1 */
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;	/* 上升沿捕获 */
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;	/* 直接映射TI1 */
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;		/* 不分频 */
	TIM_ICInitStruct.TIM_ICFilter = 0xF;				/* 滤波 */
	TIM_ICInit(TIM3, &TIM_ICInitStruct);

	/* 选择TI1FP1作为从模式触发输入 */
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
	/* 配置从模式为复位模式: 触发信号(上升沿)时复位CNT */
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);

	/* 使能TIM3 */
	TIM_Cmd(TIM3, ENABLE);
}

/**
 * @brief  获取测得的频率值
 * @note   读取CCR1捕获值 (代表信号周期)，频率 = 1MHz / CCR1
 *         返回最近一次有效捕获计算出的频率
 * @retval 频率值 (Hz)，若无信号返回0，频率过低(周期>65535us)返回0
 */
uint32_t IC_GetFrequency(void)
{
	/* 检查CC1捕获标志 */
	if (TIM_GetFlagStatus(TIM3, TIM_FLAG_CC1) == SET)
	{
		/* 清除标志位 */
		TIM_ClearFlag(TIM3, TIM_FLAG_CC1);

		/* 读取CCR1捕获值 = 信号周期(us) */
		uint16_t ccr1 = TIM_GetCapture1(TIM3);

		/* 防止除零错误，且周期不能为0 */
		if (ccr1 != 0)
		{
			/* 频率 = 1,000,000 / 周期(us) */
			return 1000000 / ccr1;
		}
	}
	return 0;
}
