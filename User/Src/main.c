#include "main.h"

extern u8 ok_bit = 0;

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
    USARTx_Init();
    NVICx_Init();
    TIMx_Init();
    EXTIx_Init();

    printf("Running...\n");
    while (1)
    {
        Key_Scan();
        // LDR_Scan();
        if (Ultrasonic_Read() <= 10)
        {
            LED_RED_ON;
            bell();
        }
        else
        {
            LED_RED_OFF;
        }
    }
}
