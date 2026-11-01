#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"

uint8_t MPU6050_ID;
int16_t Accelerometer_X,Accelerometer_Y,Accelerometer_Z,Gyroscope_X,Gyroscope_Y,Gyroscope_Z;
int main (void)
{
	OLED_Init();
	MPU6050_Init();
	OLED_ShowString(1,1,"ID:");
	MPU6050_ID=MPU6050_GetID();
	OLED_ShowHexNum(1,4,MPU6050_ID,2);
	while(1)
	{
		MPU6050_GetData(&Accelerometer_X,&Accelerometer_Y,&Accelerometer_Z,&Gyroscope_X,&Gyroscope_Y,&Gyroscope_Z);
		OLED_ShowSignedNum(2,1,Accelerometer_X,5);
		OLED_ShowSignedNum(3,1,Accelerometer_Y,5);
		OLED_ShowSignedNum(4,1,Accelerometer_Z,5);
		OLED_ShowSignedNum(2,8,Gyroscope_X,5);
		OLED_ShowSignedNum(3,8,Gyroscope_Y,5);
		OLED_ShowSignedNum(4,8,Gyroscope_Z,5);
	}
}

