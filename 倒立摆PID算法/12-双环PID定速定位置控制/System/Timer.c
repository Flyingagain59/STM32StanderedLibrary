#include "stm32f10x.h"                  // Device header
#include "Key.h"



/**
 * @brief  初始化定时器1 (TIM1) 及其相关中断配置
 * @note   该函数配置TIM1产生周期性更新中断。
 *         假设系统时钟为72MHz，预分频系数为72-1，重装载值为1000-1，
 *         则中断周期约为: (72 * 1000) / 72,000,000 = 1毫秒。
 *         按键扫描函数Key_tick在该中断中每20ms调用一次实现去抖。
 * @param  None
 * @retval None
 */
void Timer_Init (void)
{
	// 使能TIM1外设时钟 (TIM1在APB2总线上)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	// 配置TIM1使用内部时钟源
	TIM_InternalClockConfig(TIM1);
	
	// 配置TIM1时基单元参数
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1 , &TIM_TimeBaseInitStruct);
	
	// 清除TIM1更新中断标志位，防止立即触发中断
	TIM_ClearFlag(TIM1,TIM_IT_Update);
	
	// 使能TIM1更新中断
	TIM_ITConfig(TIM1 , TIM_IT_Update, ENABLE);
	
	// 配置NVIC优先级分组为组2（2位抢占优先级，2位子优先级）
	NVIC_PriorityGroupConfig (NVIC_PriorityGroup_2) ;
	
	// 配置TIM1中断通道及优先级
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init (&NVIC_InitStructure);
	
	// 启动TIM1计数器
	TIM_Cmd(TIM1,ENABLE);
}
