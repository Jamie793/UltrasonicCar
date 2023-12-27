#ifndef __JAMIEXU_NVIC_H_
#define __JAMIEXU_NVIC_H_
#include "stm32f10x.h"

void NVICx_Init(void);

void NVIC_Timer2(void);

void NVIC_EXTILine0(void);

void NVIC_USART1(void);

void NVIC_EXTILine5_9(void);


#endif
