#include "Servo.h"
#include "PWM.h"
void Servo_Init(void)
{
    PWM_Init();
}

void Servo_SetAngle(float angle)
{
    // 将角度转换为PWM占空比值
    // 假设舵机的工作范围是0-180度，对应的PWM占空比范围是500-2500 (单位: 微秒)
    // 计算公式: Compare = 500 + (angle / 180.0) * (2500 - 500)
    uint16_t compareValue = 500 + (angle * (2500 - 500)) / 180;
    PWM_SetCompare2(compareValue);
}