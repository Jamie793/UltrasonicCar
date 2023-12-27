#ifndef __JAMIEXU_USART_H_
#define __JAMIEXU_USART_H_
#include "stm32f10x.h"
#include "stdio.h"
#include "bluetooth.h"

#define MAX_RECEIVE_SIZE 50


void USARTx_Init(void);

void USART1_Init(void);

void USART1_SendBytes(u8 *buffer, u32 len);

#endif
