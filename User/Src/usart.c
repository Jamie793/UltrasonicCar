#include "usart.h"

void USARTx_Init(void)
{
    USART1_Init();
}

void USART1_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);
    USART_ClearFlag(USART1, USART_FLAG_RXNE);
    USART_Cmd(USART1, ENABLE); 
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    // USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

    // DMA_InitTypeDef DMA_InitStructure;
    // DMA_InitStructure.DMA_BufferSize = MAX_RECEIVE_SIZE;
    // DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    // DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    // DMA_InitStructure.DMA_MemoryBaseAddr = (u32)cmdData;
    // DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    // DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    // DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    // DMA_InitStructure.DMA_PeripheralBaseAddr = (u32) &(USART1->DR);
    // DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
    // DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    // DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    // DMA_Init(DMA1_Channel5, &DMA_InitStructure);
    // DMA_Cmd(DMA1_Channel5, ENABLE);
    // DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
}

void USART1_SendBytes(u8 *buffer, u32 len)
{
    for (size_t i = 0; i < len; i++)
    {
        USART_SendData(USART1, buffer[i]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
            ;
    }
}



int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (uint8_t)ch);

    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        ;

    return (ch);
}
