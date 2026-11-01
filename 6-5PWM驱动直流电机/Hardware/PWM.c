#include "stm32f10x.h"

/**
 * @brief  初始化TIM2定时器以产生PWM信号
 * @note   该函数配置PA0为复用推挽输出，设置TIM2时基参数（预分频720-1，重装载值100-1），
 *         启用CH1 PWM模式1。
 *         假设系统时钟为72MHz，则PWM频率约为1kHz (72MHz / 720 / 100)。
 * @param  无
 * @retval 无
 */
void PWM_Init (void)
{
	// 使能TIM2外设时钟 (APB1总线)
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	// 使能GPIOA外设时钟 (APB2总线)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// 定义GPIO初始化结构体变量
	GPIO_InitTypeDef GPIO_InitStructure;
	// 设置GPIO模式为复用推挽输出 (用于TIM2的PWM输出)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	// 设置GPIO引脚为Pin 1 (PA1对应TIM2_CH2)
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	// 设置GPIO最大翻转速度为50MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// 根据上述配置初始化GPIOA
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 配置TIM2使用内部时钟源 (默认即可，显式调用更清晰)
	TIM_InternalClockConfig(TIM2);
	
	// 定义TIM时基初始化结构体变量
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	// 设置时钟分频因子为1 (不分频)
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	// 设置计数器模式为向上计数模式
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	// 设置自动重装载寄存器周期值 (ARR)，决定PWM频率
	// 频率 = 72MHz / (Prescaler+1) / (Period+1) = 72M / 720 / 100 = 1kHz
	TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;
	// 设置预分频器值 (PSC)，对输入时钟进行分频
	TIM_TimeBaseInitStruct.TIM_Prescaler = 36 - 1;
	// 设置重复计数器值，高级定时器常用，通用定时器设为0
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	// 根据上述配置初始化TIM2时基单元
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
    // 定义TIM输出比较初始化结构体变量
    TIM_OCInitTypeDef TIM_OC1InitStruct;
    // 将结构体成员填充为默认值，防止未初始化成员导致错误
    TIM_OCStructInit(&TIM_OC1InitStruct);
    // 设置输出比较模式为PWM模式1
    // 当 CNT < CCR1 时输出有效电平，否则输出无效电平
    TIM_OC1InitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    // 设置输出极性为高电平有效 (即匹配时输出高，不匹配时输出低，配合PWM模式1)
    TIM_OC1InitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    // 使能输出状态 (允许引脚输出PWM信号)
    TIM_OC1InitStruct.TIM_OutputState = TIM_OutputState_Enable;
    // 设置捕获比较寄存器1的值 (CCR1)，决定初始占空比
    // 当前值为100，而Period也为99(100-1)，意味着初始占空比为100% (常高)
    // 注意：若要50%占空比，此处应设为50
 	TIM_OC1InitStruct.TIM_Pulse = 0;
    // 根据上述配置初始化TIM2通道3的输出比较功能
    TIM_OC3Init(TIM2, &TIM_OC1InitStruct);
	
	// 使能TIM2外设，开始计数并产生PWM波形
	TIM_Cmd(TIM2, ENABLE);
}

/**
 * @brief  设置TIM2通道1的比较值，从而改变PWM占空比
 * @param  Compare: 新的捕获比较值 (0-100)，决定占空比大小
 * @retval 无
 */
void PWM_SetCompare3(uint16_t Compare)
{
// 直接修改TIM2通道3的捕获比较寄存器3 (CCR3) 的值
// 这会实时更新PWM波的占空比，无需重新初始化定时器
TIM_SetCompare3(TIM2, Compare);
}
