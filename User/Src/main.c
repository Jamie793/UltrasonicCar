#include "main.h"

u8 ok_bit = 0;

void Key_Scan(void)
{
    u8 keys[3];
    keys[0] = KEY_LT_READ;
    keys[1] = KEY_MD_READ;
    keys[2] = KEY_RT_READ;

    if ((KEY_LT_READ & KEY_MD_READ & KEY_RT_READ) == 0)
    {
        SysTick_Delay_Ms(20);
        if ((KEY_LT_READ & KEY_MD_READ & KEY_RT_READ) == 0)
        {
            while ((KEY_LT_READ & KEY_MD_READ & KEY_RT_READ) == 0)
                ;

            if (keys[0] == 0)
            {
                printf("press LT key...\n");
            }
            else if (keys[1] == 0)
            {
                printf("press MD key...\n");
            }
            else if (keys[2] == 0)
            {
                printf("press RT key...\n");
            }
        }
    }
}

// void LDR_Scan(void)
// {
//     if (GPIO_ReadInputDataBit(LDR_PORT, LDR_PIN))
//     {
//         LED_GREEN_ON;
//     }else{
//         LED_GREEN_OFF;
//     }
// }

void bell(void)
{
    for (int i = 0; i < 3; i++)
    {
        BELL_ON;
        SysTick_Delay_Ms(50);
        BELL_OFF;
        SysTick_Delay_Ms(100);
    }
}

int main(void)
{
    GPIOx_Init();
    SysTick_Init();
    NVICx_Init();
    USARTx_Init();
    TIMx_Init();
    EXTIx_Init();
    Car_Init();

    // printf("Running...\n");
    PIDCar_Init();
    Car_Move_Forward();
    Car_PWM_Set(1000);
    while (1)
    {
        // printf("Current speed: A: %d, B: %d, C: %d, D: %d\n", Motor_Encoder[0], Motor_Encoder[1], Motor_Encoder[2], Motor_Encoder[3]);
        // SysTick_Delay_Ms(1000);
        // printf("%d\n", TIM_GetCounter(TIM5));
        // Key_Scan();
        // LDR_Scan();
        // if (Ultrasonic_Read() <= 10)
        // {
        //     LED_RED_ON;
        //     bell();
        // }
        // else
        // {
        //     LED_RED_OFF;
        // }
    }
}
