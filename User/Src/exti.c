#include "exti.h"

void EXTIx_Init(void)
{
    EXTILine0_Init();
    EXTILine5_9_Init();
}

void EXTILine0_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

void EXTILine5_9_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStr;
    EXTI_InitStr.EXTI_Line = EXTI_Line5 | EXTI_Line6 | EXTI_Line7 | EXTI_Line8;
    EXTI_InitStr.EXTI_LineCmd = ENABLE;
    EXTI_InitStr.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStr.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_Init(&EXTI_InitStr);
}
