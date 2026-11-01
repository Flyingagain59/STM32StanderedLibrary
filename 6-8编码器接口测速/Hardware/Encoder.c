#include "Encoder.h"
#include "stm32f10x.h"                      // 设备头文件

/**
 * 初始化编码器接口（TIM3，编码器模式3，TI1+TI2双沿计数）
 */
void Encoder_Init(void)
{
    /* ==== 1. 使能时钟 ==== */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);    // 使能TIM3时钟（APB1总线）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   // 使能GPIOA时钟（APB2总线）

    /* ==== 2. 配置GPIO引脚 ==== */
    GPIO_InitTypeDef GPIO_InitStructure;                     // 定义GPIO初始化结构体
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;            // 上拉输入（编码器断电时引脚不悬空）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;  // PA6 = TIM3_CH1, PA7 = TIM3_CH2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        // GPIO速度设置（输入模式下实际无效）
    GPIO_Init(GPIOA, &GPIO_InitStructure);                   // 将配置写入GPIOA寄存器

    /* ==== 3. 配置TIM3时基 ==== */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;          // 定义时基初始化结构体
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // 滤波器采样时钟 = TIM3CLK / 1
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;  // 计数方向（编码器模式下被硬件覆盖）
    TIM_TimeBaseInitStruct.TIM_Period = 65535;               // 自动重装载值（16位最大值）
    TIM_TimeBaseInitStruct.TIM_Prescaler = 1 - 1;           
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;        // 重复计数器（高级定时器用，这里不用）
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);         // 将配置写入TIM3寄存器

    /* ==== 4. 配置输入捕获通道，设置数字滤波器 ==== */
    TIM_ICInitTypeDef TIM_ICInitStruct;                      // 定义输入捕获初始化结构体
    TIM_ICStructInit(&TIM_ICInitStruct);                     // 填充结构体为默认值

    /* 配置通道1（TI1 -> IC1） */
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;            // 选择通道1
    TIM_ICInitStruct.TIM_ICFilter = 0xF;                     // 数字滤波器：连续采样8次一致才确认跳变
    TIM_ICInit(TIM3, &TIM_ICInitStruct);                     // 写入捕获寄存器

    /* 配置通道2（TI2 -> IC2） */
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;            // 切换到通道2
    TIM_ICInitStruct.TIM_ICFilter = 0xF;                     // 同样的滤波器配置
    TIM_ICInit(TIM3, &TIM_ICInitStruct);                     // 写入捕获寄存器

    /* ==== 5. 配置编码器模式 ==== */
    TIM_EncoderInterfaceConfig(
        TIM3,
        TIM_EncoderMode_TI12,            // 编码器模式3：TI1和TI2双沿都计数（4倍频）
        TIM_ICPolarity_Rising,           // TI1极性：不反相
        TIM_ICPolarity_Rising            // TI2极性：不反相
    );

    /* ==== 6. 启动TIM3计数器 ==== */
    TIM_Cmd(TIM3, ENABLE);                                   // CEN位置1，计数器开始计数
}

/**
 * 获取编码器当前计数值
 * @return 当前TIM3计数器值（范围-32768~32767）
 */
int16_t Encoder_GetCount(void)
{
    int16_t temp;
    temp = TIM_GetCounter(TIM3);         
    TIM_SetCounter(TIM3, 0);                                
    return temp;                             
}

