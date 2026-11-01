#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Key.h"
#include "AD.h"
#include "Motor.h"
#include "Encoder.h"
#include "serial.h"

	int16_t pwm;
	int16_t speed,location;

	float Outer_Target,Outer_Actual,Outer_Out;
	float Outer_Kp=0.3,Outer_Ki=0,Outer_Kd=0.4;
	float Outer_Error0,Outer_Error1,Outer_ErrorInit;

	float Inner_Target,Inner_Actual,Inner_Out;
	float Inner_Kp=0.3,Inner_Ki=0.3,Inner_Kd=0;
	float Inner_Error0,Inner_Error1,Inner_ErrorInit;

int main (void)
{
	Motor_Init();
	OLED_Init();
	Key_Init();
	Timer_Init();
	Encoder_Init();
	AD_Init();
	Serial_Init();

	OLED_Printf(0,0,OLED_8X16,"Speed Control");
	OLED_Update();

	while (1)
	{
//		keynum = Key_GetNumber();
//		if (keynum == 1)
//		{
//			Inner_Target += 10;
//		}if (keynum == 2)
//		{
//			Inner_Target -=10;
//		}if (keynum == 3)
//		{
//			Inner_Target = 0;
//		}
//		Inner_Kp = AD_Getvalue(1)/4095.0 * 2;
//		Inner_Ki = AD_Getvalue(2)/4095.0 * 2;
//		Inner_Kd = AD_Getvalue(3)/4095.0 * 2;

		Inner_Target = AD_Getvalue(4)/4095.0 *300 - 150;
//		OLED_Printf(0,16,OLED_8X16,"Kp:%4.2f",Inner_Kp);
//		OLED_Printf(0,32,OLED_8X16,"Ki:%4.2f",Inner_Ki);
//		OLED_Printf(0,48,OLED_8X16,"Kd:%4.2f",Inner_Kd);

//		OLED_Printf(64,16,OLED_8X16,"tar:%+04.0f",Inner_Target);
//		OLED_Printf(64,32,OLED_8X16,"act:%+04.0f",Inner_Actual);
//		OLED_Printf(64,48,OLED_8X16,"out:%+04.0f",Inner_Out);

		OLED_Update();
		Serial_Printf("%f,%f,%f\r\n",Inner_Target,Inner_Actual,Inner_Out);
		
		
		Outer_Kp = AD_Getvalue(1)/4095.0 * 2;
		Outer_Ki = AD_Getvalue(2)/4095.0 * 2;
		Outer_Kd = AD_Getvalue(3)/4095.0 * 2;

		Outer_Target = AD_Getvalue(4)/4095.0 *816 - 408;
		OLED_Printf(0,16,OLED_8X16,"Kp:%4.2f",Outer_Kp);
		OLED_Printf(0,32,OLED_8X16,"Ki:%4.2f",Outer_Ki);
		OLED_Printf(0,48,OLED_8X16,"Kd:%4.2f",Outer_Kd);

		OLED_Printf(64,16,OLED_8X16,"tar:%+04.0f",Outer_Target);
		OLED_Printf(64,32,OLED_8X16,"act:%+04.0f",Outer_Actual);
		OLED_Printf(64,48,OLED_8X16,"out:%+04.0f",Outer_Out);

		OLED_Update();
		Serial_Printf("%f,%f,%f\r\n",Outer_Target,Outer_Actual,Outer_Out);
	}
}
void TIM1_UP_IRQHandler(void)
{
	static uint16_t cnt1 = 0 , cnt2 = 0;
	if (TIM_GetITStatus(TIM1 , TIM_IT_Update) == SET)
	{
		Key_tick();

		cnt1++;
		if(cnt1 >= 40)
		{
			cnt1 = 0;
			speed = Encoder_GetCount();
			location += speed;

			Inner_Actual = speed;

			Inner_Error1 = Inner_Error0;
			Inner_Error0 = Inner_Target - Inner_Actual;
			if(Inner_Ki != 0)
			{
				Inner_ErrorInit += Inner_Error0;
			}
			else
			{
				Inner_ErrorInit = 0;
			}
			
			Inner_Out = Inner_Kp*Inner_Error0 + Inner_Ki*Inner_ErrorInit + Inner_Kd*(Inner_Error0 - Inner_Error1);

			if (Inner_Out > 100)
			{
				Inner_Out = 100;
			}
			if (Inner_Out < -100)
			{
				Inner_Out = -100;
			}

			Motor_SetPWM(Inner_Out);
		}
		cnt2++;
		if(cnt2 >= 40)
		{
			cnt2 = 0;
			Outer_Actual = location;

			Outer_Error1 = Outer_Error0;
			Outer_Error0 = Outer_Target - Outer_Actual;
			if(Outer_Ki != 0)
			{
				Outer_ErrorInit += Outer_Error0;
			}
			else
			{
				Outer_ErrorInit = 0;
			}
			
			Outer_Out = Outer_Kp*Outer_Error0 + Outer_Ki*Outer_ErrorInit + Outer_Kd*(Outer_Error0 - Outer_Error1);

			if (Outer_Out > 150)
			{
				Outer_Out = 150;
			}
			if (Outer_Out < -150)
			{
				Outer_Out = -150;
			}

			Inner_Target = Outer_Out;
		} 
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
	}
}
