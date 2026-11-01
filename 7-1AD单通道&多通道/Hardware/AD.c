#include "stm32f10x.h"
#include "AD.h"

void AD_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);      // 使能ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);     // 使能GPIOA时钟

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);                        // 配置ADC时钟6分频

    GPIO_InitTypeDef GPIO_InitStructure;                       // 定义GPIO初始化结构体
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;                 // 选择引脚0-3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;             // 模拟输入模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         // 速度50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                    // 初始化GPIO


    ADC_InitTypeDef ADC_InitStructure;                        // 定义ADC初始化结构体
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        // 独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;             // 单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        // 连续转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;    // 数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;                   // 通道数为1
    ADC_Init(ADC1, &ADC_InitStructure);                       // 初始化ADC

    ADC_Cmd(ADC1, ENABLE);                                    // 使能ADC
    ADC_ResetCalibration(ADC1);                               // 复位校准
    while (ADC_GetResetCalibrationStatus(ADC1));              // 等待复位校准完成
    ADC_StartCalibration(ADC1);                               // 开始校准
    while (ADC_GetCalibrationStatus(ADC1));                   // 等待校准完成
}
uint16_t AD_Getvalue(uint8_t ADC_Channel)
{
    ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5); // 配置规则通道，采样时间55.5周期
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);           // 启动软件触发转换
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);  // 等待转换结束
    return ADC_GetConversionValue(ADC1);              // 读取转换结果
}
