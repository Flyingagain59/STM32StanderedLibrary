#include "MyI2C.h"
#include "stm32f10x.h"
#include "Delay.h"

void My_IIC_W_SCL(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB , GPIO_Pin_10 , (BitAction)BitValue);
    Delay_us(10);
}
void My_IIC_W_SDA(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB , GPIO_Pin_11 , (BitAction)BitValue);
    Delay_us(10);
}
uint8_t My_IIC_Read (void)
{
  uint8_t BitValue;
  BitValue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
  Delay_us(10);
  return BitValue;
}
/**
  * @brief  初始化软件I2C的GPIO引脚
  * @param  无
  * @retval 无
  * @note   使用GPIOB的Pin10和Pin11作为I2C的SCL和SDA线
  *         配置为开漏输出模式，初始状态为低电平
  */
void My_IIC_Init (void)
{   
    // 使能GPIOB外设时钟，为GPIO操作提供时钟源
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE);

    // 定义GPIO初始化结构体变量
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 配置GPIO模式为开漏输出模式（Out_OD），适用于I2C总线
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    
    // 选择Pin10和Pin11，分别用作I2C的SCL和SDA信号线
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 |GPIO_Pin_11;
    
    // 设置GPIO输出速度为50MHz，确保信号响应速度
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    // 根据配置参数初始化GPIOB的对应引脚
    GPIO_Init(GPIOB , &GPIO_InitStructure);
    
    // 将Pin10和Pin11初始化为低电平状态
    GPIO_ResetBits (GPIOB , GPIO_Pin_10|GPIO_Pin_11);
}

void My_IIC_Start(void)
{
    My_IIC_W_SDA(1);
    My_IIC_W_SCL(1);
    My_IIC_W_SDA(0);
    My_IIC_W_SCL(0);
}
void My_IIC_Stop(void)
{
  My_IIC_W_SDA(0);
  My_IIC_W_SCL(1);
  My_IIC_W_SDA(1);
}
void My_IIC_SendByte(uint8_t Byte)
{
  uint8_t i;
  for ( i = 0; i < 8; i++)
  {
    My_IIC_W_SDA(Byte & (0x80>>i));
    My_IIC_W_SCL(1);
    My_IIC_W_SCL(0);
  }
}
uint8_t My_IIC_ReceiveByte(void)
{
  uint8_t Byte = 0x00;
  My_IIC_W_SDA(1);
  for (int i = 0; i < 8; i++)
  {
    My_IIC_W_SCL(1);
    if(My_IIC_Read() == 1)
    {
      Byte |= (0x80 >>i);
    }
     My_IIC_W_SCL(0);    
  }
  return Byte;
}
void My_IIC_SendAck(uint8_t Ackbit)
{
    My_IIC_W_SDA(Ackbit);
    My_IIC_W_SCL(1);
    My_IIC_W_SCL(0);
}
uint8_t My_IIC_ReceiveAck(void)
{
    uint8_t Ackbit;
    My_IIC_W_SDA(1);
    My_IIC_W_SCL(1);
    Ackbit = My_IIC_Read();
    My_IIC_W_SCL(0);    
    return Ackbit;
}
