#include "stm32f10x.h"
#include "AD.h"

uint16_t AD_Value[4];  // 定义一个数组用于存储ADC转换结果，长度为4


void AD_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);      // 使能ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);     // 使能GPIOA时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  // 开启DMA1时钟，DMA挂在AHB总线

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);                        // 配置ADC时钟6分频

    GPIO_InitTypeDef GPIO_InitStructure;                       // 定义GPIO初始化结构体
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;                 // 选择引脚0-3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;             // 模拟输入模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         // 速度50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                    // 初始化GPIO

    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5); // 配置规则通道，采样时长5.5周期
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5); // 配置规则通道，采样时长5.5周期
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5); // 配置规则通道，采样时长5.5周期
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5); // 配置规则通道，采样时长5.5周期


    ADC_InitTypeDef ADC_InitStructure;                        // 定义ADC初始化结构体
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        // 独立模式
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;             // 扫描转换模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;        // 连续转换模式关闭
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;    // 数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 4;                   // 通道数为4
    ADC_Init(ADC1, &ADC_InitStructure);                       // 初始化ADC

	
	DMA_InitTypeDef DMA_InitStructure;      // 定义DMA初始化结构体变量
	// 配置外设（源）--------------------------------------------------------
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;           // 设置外设基地址为源数据地址
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  // 外设数据宽度8位
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;          // 外设地址自增：使能，每传完一个字节地址+1

	// 配置存储器（目标）----------------------------------------------------
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;               // 设置存储器基地址为目标数据地址
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;          // 存储器数据宽度：16位（半字
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                  // 存储器地址自增：使能，每接收一个半字地址+2

	// 配置传输方向和数据量 -----------------------------------------------------
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;         // 传输方向：外设作为数据源（从外设读到存储器）
    DMA_InitStructure.DMA_BufferSize = 4;                   // 设置缓冲区大小，即要传输的数据量

	// 配置传输模式和优先级 -----------------------------------------------------
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;              // 传输模式：正常模式（单次传输，非循环传输）
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                // 存储器到内存：不使能（DMA传输数据到存储器）
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;        // DMA优先级：高优先级

	// 初始化DMA通道 -----------------------------------------------------------
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);               // 根据结构体参数初始化DMA1通道1
    DMA_Cmd(DMA1_Channel1, ENABLE);                           // 先关闭DMA通道，等待调用传输函数时再开

    ADC_DMACmd(ADC1, ENABLE);                                  // 使能DMA请求

    ADC_Cmd(ADC1, ENABLE);                                    // 使能ADC
    ADC_ResetCalibration(ADC1);                               // 复位校准+
    while (ADC_GetResetCalibrationStatus(ADC1));              // 等待复位校准完成
    ADC_StartCalibration(ADC1);                               // 开始校验
    while (ADC_GetCalibrationStatus(ADC1));                   // 等待校准完成
}



void AD_Getvalue(void)
{
    DMA_Cmd(DMA1_Channel1, DISABLE);                         // 关闭DMA通道1
    DMA_SetCurrDataCounter(DMA1_Channel1, 4);                // 设置当前数据计数器为4，即要传输的数据�?
    DMA_Cmd(DMA1_Channel1, ENABLE);                         // 开启DMA通道1

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);                // 软件触发ADC转换

    while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);       // 等待转换完成标志位被设置   
    DMA_ClearFlag(DMA1_FLAG_TC1);                        // 清除传输完成标志�?
}
