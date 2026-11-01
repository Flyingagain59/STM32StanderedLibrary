#include "DMA.h"                          // DMA驱动头文件
#include "stm32f10x.h"                    // STM32标准库头文件

static uint16_t DMA_Size;                   // 静态变量，保存DMA传输数据量，供传输函数使用

/**
 * @brief  DMA初始化函数
 * @param  AddrA: 源地址（外设基地址），即数据从何处读出
 * @param  AddrB: 目标地址（存储器基地址），即数据写入何处
 * @param  Size:  传输数据量，单位为字节
 * @retval 无
 */
void MyDMA_Init(uint32_t AddrA ,uint32_t AddrB , uint16_t Size)
{
    DMA_Size = Size;                        // 保存数据量到静态变量，供后续传输使用
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  // 开启DMA1时钟，DMA挂在AHB总线上
	
	DMA_InitTypeDef DMA_InitStructure;      // 定义DMA初始化结构体变量
	
	// 配置外设（源）参数 --------------------------------------------------------
	DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;           // 设置外设基地址为源数据地址
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  // 外设数据宽度：8位（字节）
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;          // 外设地址自增：使能，每传完一个字节地址+1

	// 配置存储器（目标）参数 ----------------------------------------------------
	DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;               // 设置存储器基地址为目标数据地址
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;          // 存储器数据宽度：8位（字节）
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                  // 存储器地址自增：使能，每接收一个字节地址+1

	// 配置传输方向和数据量 -----------------------------------------------------
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;         // 传输方向：外设作为数据源（从外设读到存储器）
    DMA_InitStructure.DMA_BufferSize = Size;                   // 设置缓冲区大小，即要传输的数据量

	// 配置传输模式和优先级 -----------------------------------------------------
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;              // 传输模式：正常模式（单次传输，非循环）
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;                // 存储器到存储器模式：使能（软件触发）
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;        // DMA优先级：高优先级

	// 初始化DMA通道 -----------------------------------------------------------
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);               // 根据结构体参数初始化DMA1通道1

    DMA_Cmd(DMA1_Channel1, DISABLE);                           // 先关闭DMA通道，等待调用传输函数时再开启
}

/**
 * @brief  DMA数据传输函数
 * @param  无
 * @retval 无
 * @note   执行一次DMA传输，从源地址传输数据到目标地址
 */
void MyDMA_Transfer(void)
{
    DMA_Cmd(DMA1_Channel1, DISABLE);                           // 关闭DMA通道，确保可以重新设置参数
    
    DMA_SetCurrDataCounter(DMA1_Channel1, DMA_Size);           // 重新设置当前数据计数器，恢复传输数据量
    
    DMA_Cmd(DMA1_Channel1, ENABLE);                            // 使能DMA通道，开始传输

    // 等待传输完成标志位（阻塞方式）
    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);          // 查询通道1传输完成标志，RESET表示未完成，循环等待

    DMA_ClearFlag(DMA1_FLAG_TC1);                              // 清除传输完成标志位，为下次传输做准备
}
