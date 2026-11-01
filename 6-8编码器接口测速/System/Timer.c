#include "stm32f10x.h"                  // Device header

extern uint16_t number;


/**
 * @brief  初始化定时器2 (TIM2) 及其相关中断配置
 * @note   该函数配置TIM2产生周期性更新中断。
 *         假设系统时钟为72MHz，预分频系数为7200-1，重装载值为10000-1，
 *         则中断周期约为: (7200 * 10000) / 72,000,000 = 1秒。
 * @param  None
 * @retval None
 */
void Timer_Init (void)
{
	// 使能TIM2外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	// 配置TIM2使用内部时钟源
	TIM_InternalClockConfig(TIM2);
	
	// 配置TIM2时基单元参数
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 10000 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2 , &TIM_TimeBaseInitStruct);
	
	// 清除TIM2更新中断标志位，防止立即触发中断
	TIM_ClearFlag(TIM2,TIM_IT_Update);
	
	// 使能TIM2更新中断
	TIM_ITConfig(TIM2 , TIM_IT_Update, ENABLE);
	
	// 配置NVIC优先级分组为组2（2位抢占优先级，2位子优先级）
	NVIC_PriorityGroupConfig (NVIC_PriorityGroup_2) ;
	
	// 配置TIM2中断通道及优先级
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init (&NVIC_InitStructure);
	
	// 启动TIM2计数器
	TIM_Cmd(TIM2,ENABLE);
}
/**
  * @brief  TIM2定时器中断服务函数
  * @param  无
  * @retval 无
  * @note   当TIM2产生更新中断时自动调用此函数，每秒执行一次
  */

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) // 检查TIM2更新中断标志位
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);   // 清除中断标志位
		number = Encoder_GetCount();                  // 读取编码器计数值
		TIM_SetCounter(TIM3, 0);                      // 清零计数器，准备下一次计数
	}
}