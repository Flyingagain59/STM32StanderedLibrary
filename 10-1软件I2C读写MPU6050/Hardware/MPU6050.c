#include "MPU6050.h"
#include "MPU6050_Reg.h"
#define MPU6050_ADDR 0xD0

void MPU6050_WriteReg(uint8_t reg, uint8_t data)
{
    My_IIC_Start();
    My_IIC_SendByte(MPU6050_ADDR);
    My_IIC_ReceiveAck();
    My_IIC_SendByte(reg);
    My_IIC_ReceiveAck();
    My_IIC_SendByte(data);
    My_IIC_ReceiveAck();
    My_IIC_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t reg)
{
    uint8_t data ;

    My_IIC_Start();
    My_IIC_SendByte(MPU6050_ADDR);
    My_IIC_ReceiveAck();
    My_IIC_SendByte(reg);
    My_IIC_ReceiveAck();

    My_IIC_Start();
    My_IIC_SendByte(MPU6050_ADDR | 0x01);
    My_IIC_ReceiveAck();
    data = My_IIC_ReceiveByte();
    My_IIC_SendAck(1);
    My_IIC_Stop();

    return data;
}

void MPU6050_Init(void)
{
    My_IIC_Init();
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
    MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}
void MPU6050_GetData (int16_t *accx, int16_t *accy, int16_t *accz,int16_t *gyrox, int16_t *gyroy, int16_t *gyroz)
{
    uint8_t DataH,DataL;
    DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
    *accx = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
    *accy = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
    *accz = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
    *gyrox = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
    *gyroy = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
    *gyroz = (DataH << 8) | DataL;
}
uint8_t MPU6050_GetID (void)
{
    return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}