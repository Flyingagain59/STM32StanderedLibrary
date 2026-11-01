#ifndef _MPU6050_H_
#define _MPU6050_H_
#include "MyI2C.h"

uint8_t MPU6050_GetID (void);
void MPU6050_Init(void);
uint8_t MPU6050_ReadReg(uint8_t reg);
void MPU6050_WriteReg(uint8_t reg, uint8_t data);
void MPU6050_GetData (int16_t *accx, int16_t *accy, int16_t *accz,int16_t *gyrox, int16_t *gyroy, int16_t *gyroz);
#endif
