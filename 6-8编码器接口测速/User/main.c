#include "stm32f10x.h"                  // 设备头文件
#include "OLED.h"                       // OLED显示模块头文件
#include "Encoder.h"     
#include "Timer.h"               // 编码器模块头文件
int16_t number;                        // 全局变量：存放编码器当前计数值

/**
 * 主函数：初始化外设，循环显示编码器计数值
 */
int main(void)
{
    /* ---- 外设初始化 ---- */
    Encoder_Init();                     // 初始化TIM3编码器接口（PA6=CH1, PA7=CH2）
    OLED_Init();                        
	Timer_Init();
    /* 在OLED第1行第1列显示提示字符串 */
    OLED_ShowString(1, 1, "speed: ");     // 显示5个ASCII字符："Cnt: "

    /* ---- 主循环：不断读取编码器并刷新显示 ---- */
    while(1)                            // 无限循环
    {
        OLED_ShowSignedNum(1, 7, number, 5);  
    }
}

