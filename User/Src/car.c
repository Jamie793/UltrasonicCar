#include "car.h"

void Car_Turn_Left(void)
{
    MOTOR_A_CCW; 
    MOTOR_B_CW;
    MOTOR_C_CCW;
    MOTOR_D_CW;
}

void Car_Turn_Right(void)
{
    MOTOR_A_CW;
    MOTOR_B_CCW;
    MOTOR_C_CW;
    MOTOR_D_CCW;
}

void Car_Move_Forward(void)
{
    MOTOR_A_CW;
    MOTOR_B_CW;
    MOTOR_C_CW;
    MOTOR_D_CW;
}

void Car_Move_Back(void)
{
    MOTOR_A_CCW;
    MOTOR_B_CCW;
    MOTOR_C_CCW;
    MOTOR_D_CCW;
}

void Car_Move_Left(void)
{
    MOTOR_A_CCW;
    MOTOR_B_CW; 
    MOTOR_C_CW;
    MOTOR_D_CCW;
}

void Car_Move_Right(void)
{
    MOTOR_A_CW;
    MOTOR_B_CCW;
    MOTOR_C_CCW;
    MOTOR_D_CW;
}

void Car_PWM_Set(u32 speed)
{
    TIM3->CCR1 = 0;
    TIM3->CCR2 = 0;
    TIM3->CCR3 = 0;
    TIM3->CCR4 = 0;
}
