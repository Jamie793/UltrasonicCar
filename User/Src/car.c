#include "car.h"

u32 Motor_Encoder[4];

void Car_Init(void)
{
    MOTOR_A_STBY_H;
    MOTOR_B_STBY_H;
    // Car_PWM_Set(100);
    // Car_Turn_Left();
}

void Car_Turn_Left(void)
{
    MOTOR_A_CW;
    MOTOR_B_CCW;
    MOTOR_C_CCW;
    MOTOR_D_CW;
}

void Car_Turn_Right(void)
{
    MOTOR_A_CCW;
    MOTOR_B_CW;
    MOTOR_C_CW;
    MOTOR_D_CCW;
}

void Car_Move_Forward(void)
{
    MOTOR_A_CW;
    MOTOR_B_CW;
    MOTOR_C_CCW;
    MOTOR_D_CCW;
}

void Car_Move_Backward(void)
{
    MOTOR_A_CCW;
    MOTOR_B_CCW;
    MOTOR_C_CW;
    MOTOR_D_CW;
}

void Car_Move_Left(void)
{
    MOTOR_A_CCW;
    MOTOR_B_CW;
    MOTOR_C_CCW;
    MOTOR_D_CW;
}

void Car_Move_Right(void)
{

    MOTOR_A_CW;
    MOTOR_B_CCW;
    MOTOR_C_CW;
    MOTOR_D_CCW;
}

// void Car_PWM_Set(u32 speed)
// {
//     if (speed > 100)
//         return;

//     speed = 65535 * (speed / 100.0);
//     TIM3->CCR1 = speed;
//     TIM3->CCR2 = speed;
//     TIM3->CCR3 = speed;
//     TIM3->CCR4 = speed;
// }

void Car_PWM_Set(u32 speed)
{
    // if (speed > 100)
    //     return;

    TIM3->CCR1 = speed;
    TIM3->CCR2 = speed;
    TIM3->CCR3 = speed;
    TIM3->CCR4 = speed;
}
