#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Key.h"
#include "AD.h"
#include "Motor.h"
#include "Encoder.h"
#include "serial.h"
#include "led.h"

	int16_t pwm;
	uint8_t keynum;
	int16_t speed;
	uint8_t Motor_Flag = 1;

	float Target,Actual,Out;
	float Kp=0,Ki=0,Kd=0;
	float Error0,Error1,ErrorInit;

int main (void)
{
	Motor_Init();
	OLED_Init();
	Key_Init();
	Timer_Init();
	Encoder_Init();
	AD_Init();
	Serial_Init();
	LED_Init();
	OLED_Printf(0,0,OLED_8X16,"Speed Control");
	OLED_Update();

	while (1)
	{
		keynum = Key_GetNumber();
		if (keynum == 1)
		{
			Motor_Flag = !Motor_Flag;
		}if (Motor_Flag)
		{
			LED_ON();
		}else{
			LED_OFF();
		}
		
		Kp = AD_Getvalue(1)/4095.0 * 2;
		Ki = AD_Getvalue(2)/4095.0 * 2;
		Kd = AD_Getvalue(3)/4095.0 * 2;

		Target = AD_Getvalue(4)/4095.0 *300 - 150;
		OLED_Printf(0,16,OLED_8X16,"Kp:%4.2f",Kp);
		OLED_Printf(0,32,OLED_8X16,"Ki:%4.2f",Ki);
		OLED_Printf(0,48,OLED_8X16,"Kd:%4.2f",Kd);

		OLED_Printf(64,16,OLED_8X16,"tar:%+04.0f",Target);
		OLED_Printf(64,32,OLED_8X16,"act:%+04.0f",Actual);
		OLED_Printf(64,48,OLED_8X16,"out:%+04.0f",Out);

		OLED_Update();
		Serial_Printf("%f,%f,%f,%f\r\n",Target,Actual,Out,ErrorInit);
	}
}
void TIM1_UP_IRQHandler(void)
{
	static uint16_t cnt = 0;
	if (TIM_GetITStatus(TIM1 , TIM_IT_Update) == SET)
	{
		cnt++;
		if(cnt >= 40)
		{
			cnt = 0;
			speed = Encoder_GetCount();
			Actual = speed;

			Error1 = Error0;
			Error0 = Target - Actual;

			ErrorInit += Error0;

			if(ErrorInit > 500)
			{
				ErrorInit = 500;
			}if (ErrorInit < -500)
			{
				ErrorInit = -500;
			}
			
			Out = Kp*Error0 + Ki*ErrorInit + Kd*(Error0 - Error1);

			if (Out > 100)
			{
				Out = 100;
			}
			if (Out < -100)
			{
				Out = -100;
			}

			if(Motor_Flag )
			{
				Motor_SetPWM(Out);	
			}else{
				Motor_SetPWM(0);	
			}
		}
		Key_tick();
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
	}
}
