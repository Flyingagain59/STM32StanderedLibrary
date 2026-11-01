#include "Serial.h"
#include "stm32f10x.h"
#include "stdio.h"

char serial_RxPacket[100] ;
uint8_t RXflag = 0;

/**
  * @brief  串口初始化函数，配置USART1参数
  * @param  无
  * @retval 无
  */
void Serial_Init(void)
{
    // 开启USART1时钟，USART1挂载在APB2总线上
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
    // 开启GPIOA时钟，USART1的TX(PA9)和RX(PA10)在GPIOA中
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

    // 定义GPIO初始化结构体变量
    GPIO_InitTypeDef GPIO_InitStructure;
    // 配置PA9为串口发送引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
    // 复用推挽输出模式，用于USART1_TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
    // GPIO输出速度50MHz
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    // 根据结构体参数初始化GPIOA
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
    
    // 配置PA10为串口接收引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
    // 上拉模式，用于USART1_RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
    // GPIO输出速度50MHz
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    // 根据结构体参数初始化GPIOA
    GPIO_Init(GPIOA, &GPIO_InitStructure); 

    // 定义USART初始化结构体变量
    USART_InitTypeDef USART_InitStructure;
    // 设置波特率为9600，通信双方需保持一致
    USART_InitStructure.USART_BaudRate = 9600;
    // 数据位长度为8位
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    // 停止位为1位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    // 无奇偶校验
    USART_InitStructure.USART_Parity = USART_Parity_No;
    // 无硬件流控制
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    // 仅使能发送模式
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    // 根据结构体参数初始化USART1
    USART_Init(USART1, &USART_InitStructure);


    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    // 使能USART1，开始工作
    USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  串口发送一个字节数据
  * @param  byte 要发送的字节数据，范围：0x00~0xFF
  * @retval 无
  */
void Serial_SendByte(uint8_t byte)
{
    // 等待发送数据寄存器为空，TXE=1时表示可以写入新数据
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    // 将要发送的字节写入USART1的数据寄存器DR，启动发送
    USART_SendData(USART1, byte);
}
void Serial_SendArray(uint8_t *array, uint16_t length)
{
    for (int i = 0; i < length; i++) {
        Serial_SendByte(array[i]);
    }
}
void Serial_SendString(char *str)
{
    while (*str != '\0') {
        Serial_SendByte(*str++);
    }
}
uint32_t Serial_Pow(uint32_t x, uint32_t y)
{
    uint32_t result = 1;
    while (y--) {
        result *= x;
    }
    return result;
}
void Serial_SendNumber(uint32_t num ,uint32_t length)
{
    uint32_t i = 0;
    for (i = 0; i < length; i++) {
        Serial_SendByte((num / Serial_Pow(10, length - i - 1)) % 10 + '0');
    }
}
int fputc(int ch, FILE *f)
{
    Serial_SendByte((uint8_t)ch);
    return ch;
}

/**
  * @brief  USART1中断服务函数，使用状态机接收数据包
  * @param  无
  * @retval 无
  * @note   数据包格式：包头(0xFF) + 4字节数据 + 包尾(0xFE)
  *         Rxstate=0: 等待包头0xFF
  *         Rxstate=1: 接收4字节数据到serial_RxPacket数组
  *         Rxstate=2: 等待包尾0xFE，接收完成置位RXflag
  */
void USART1_IRQHandler(void)
{
    static uint8_t Rxstate = 0;
    static uint8_t pRxstate = 0;

    if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        uint8_t Rxdata = USART_ReceiveData(USART1);
        if(Rxstate == 0)
        {
            if(Rxdata == '@' && RXflag == 0)
            {
                Rxstate = 1;
                pRxstate = 0;
            }
        }else if(Rxstate == 1)
        {
            if(Rxdata == '\r')
            {
                Rxstate = 2; 
            }
            else
            {
                serial_RxPacket[pRxstate++] = Rxdata;
            }
        } else if(Rxstate == 2)
        {
            if(Rxdata == '\n')
            {
                RXflag = 1;
                serial_RxPacket[pRxstate++] = '\0';
                Rxstate = 0;
            }
        }
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

