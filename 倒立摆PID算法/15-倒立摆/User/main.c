#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Key.h"
#include "AD.h"
#include "Motor.h"
#include "Encoder.h"
#include "serial.h"
#include "RP.h"
#include "LED.h"
#include "PID.h"

#define CENTER_ANGLE 		2100
#define CENTER_RANGE		500
uint8_t keynum;
uint8_t RunState;
uint16_t Angle;
int16_t Speed,Location;

PID_t AnglePID = {
	.target = CENTER_ANGLE,
	
	.Kp = 0.3,
	.Ki = 0.01,
	.Kd = 0.4,

	.maxOut = 100,
	.minOut = -100,
};

PID_t LocationPID = {
	.target = 0,
	
	.Kp = 0.4,
	.Ki = 0.02,
	.Kd = 4.0,

	.maxOut = 100,
	.minOut = -100,
};

int main (void)
{

	OLED_Init();
	AD_Init();
	LED_Init();
	Motor_Init();
	Encoder_Init();
	Key_Init();
	RP_Init();
	Serial_Init();
	Timer_Init();

	while (1)
	{
		keynum = Key_GetNumber(); 
		if (keynum == 1)
		{
			RunState = !RunState;
		}
		if (RunState)
		{
			LED_ON();
		}else{
			LED_OFF();
		}

//		AnglePID.Kp = RP_Getvalue(1)/4095.0;
//		AnglePID.Ki = RP_Getvalue(2)/4095.0;
//		AnglePID.Kd = RP_Getvalue(3)/4095.0;
//		LocationPID.Kp = RP_Getvalue(1)/4095.0;
//		LocationPID.Ki = RP_Getvalue(2)/4095.0;
//		LocationPID.Kd = RP_Getvalue(3)/4095.0*9;


		OLED_Printf(0,0,OLED_6X8,"Angle");
		OLED_Printf(0,12,OLED_6X8,"Kp:%05.3f",AnglePID.Kp);
		OLED_Printf(0,20,OLED_6X8,"Ki:%05.3f",AnglePID.Ki);
		OLED_Printf(0,28,OLED_6X8,"Kd:%05.3f",AnglePID.Kd);
		OLED_Printf(0,40,OLED_6X8,"Tar:%04.0f",AnglePID.target);
		OLED_Printf(0,48,OLED_6X8,"Act:%04d",Angle);
		OLED_Printf(0,56,OLED_6X8,"Out:%+04.0f",AnglePID.out);
		
		OLED_Printf(64,0,OLED_6X8,"Location");
		OLED_Printf(64,12,OLED_6X8,"Kp:%05.3f",LocationPID.Kp);
		OLED_Printf(64,20,OLED_6X8,"Ki:%05.3f",LocationPID.Ki);
		OLED_Printf(64,28,OLED_6X8,"Kd:%05.3f",LocationPID.Kd);
		OLED_Printf(64,40,OLED_6X8,"Tar:%+05.0f",LocationPID.target);
		OLED_Printf(64,48,OLED_6X8,"Act:%+05d",Location);
		OLED_Printf(64,56,OLED_6X8,"Out:%+04.0f",LocationPID.out);

		OLED_Update();
	}
}
void TIM1_UP_IRQHandler(void)
{
	static uint16_t count1 = 0,count2 = 0;
	if (TIM_GetITStatus(TIM1 , TIM_IT_Update) == SET)
	{
		Key_tick();
		Angle = AD_Getvalue();
		Speed = Encoder_GetCount();
		Location += Speed;

		if (!(Angle > CENTER_ANGLE - CENTER_RANGE && Angle < CENTER_ANGLE + CENTER_RANGE))
		{
			RunState = 0;
		}
		
		if (RunState)
		{
			count1++;
			if(count1 >= 5)
			{
				count1 = 0;
				AnglePID.actual = Angle;
				PID_Update (&AnglePID);
				Motor_SetPWM(AnglePID.out);
			}
			count2++;
			if(count2 >= 50)
			{
				count2 = 0;
				LocationPID.actual = Location;
				PID_Update (&LocationPID);
				AnglePID.target = - LocationPID.out + CENTER_ANGLE;
			}
		}else{
			Motor_SetPWM(0);
		}
		
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
	}
}
