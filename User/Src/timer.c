#include "timer.h"

void TIMx_Init(void)
{
    TIM2_Init();
    TIM3_Init();
}

void TIM2_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
    TIM_TimBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimBaseInitStructure.TIM_Prescaler = (72 - 1);
    TIM_TimBaseInitStructure.TIM_Period = (65535 - 1);
    TIM_TimeBaseInit(TIM2, &TIM_TimBaseInitStructure);
    TIM_Cmd(TIM2, DISABLE);
}

void TIM3_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
    TIM_TimBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimBaseInitStructure.TIM_Prescaler = (72 - 1);
    TIM_TimBaseInitStructure.TIM_Period = (65535 - 1);
    TIM_TimeBaseInit(TIM3, &TIM_TimBaseInitStructure);
    TIM_Cmd(TIM3, DISABLE);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
}
