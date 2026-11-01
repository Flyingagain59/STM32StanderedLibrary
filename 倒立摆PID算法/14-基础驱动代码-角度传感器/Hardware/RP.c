#include "stm32f10x.h"
#include "RP.h"

void RP_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);      // 使能ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);     // 使能GPIOA时钟

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);                        // 配置ADC时钟6分频

    GPIO_InitTypeDef GPIO_InitStructure;                       // 定义GPIO初始化结构体
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_2 | GPIO_Pin_3;                 // 选择引脚0-3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;             // 模拟输入模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         // 速度50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                    // 初始化GPIO


    ADC_InitTypeDef ADC_InitStructure;                        // 定义ADC初始化结构体
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        // 独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;             // 单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;       // 连续转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;    // 数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;                   // 通道数为1
    ADC_Init(ADC2, &ADC_InitStructure);                       // 初始化ADC

    ADC_Cmd(ADC2, ENABLE);                                    // 使能ADC
    ADC_ResetCalibration(ADC2);                               // 复位校准
    while (ADC_GetResetCalibrationStatus(ADC2));              // 等待复位校准完成
    ADC_StartCalibration(ADC2);                               // 开始校准
    while (ADC_GetCalibrationStatus(ADC2));                   // 等待校准完成
}
uint16_t RP_Getvalue(uint8_t n)
{
    if (n == 1)
    {
        ADC_RegularChannelConfig(ADC2 , ADC_Channel_2 , 1 , ADC_SampleTime_55Cycles5);
    } else if (n == 2)
    {
        ADC_RegularChannelConfig(ADC2 , ADC_Channel_3 , 1 , ADC_SampleTime_55Cycles5);
    } else if (n == 3)
    {
        ADC_RegularChannelConfig(ADC2 , ADC_Channel_4 , 1 , ADC_SampleTime_55Cycles5);
    } else if (n ==4)
    {
        ADC_RegularChannelConfig(ADC2 , ADC_Channel_5 , 1 , ADC_SampleTime_55Cycles5);
    }
    
    ADC_SoftwareStartConvCmd(ADC2, ENABLE);           // 启动软件触发转换
    while (ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET);  // 等待转换结束
    return ADC_GetConversionValue(ADC2);              // 读取转换结果
}
