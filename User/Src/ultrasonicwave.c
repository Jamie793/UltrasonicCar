#include "ultrasonicwave.h"

extern float distance = 0;

void Ultrasonic_Start(void)
{
    while (ECHO_READ)
        ;
    GPIO_SetBits(HC_SR04_TRIG_PORT, HC_SR04_TRIG_PIN);
    SysTick_Delay_Us(20);
    GPIO_ResetBits(HC_SR04_TRIG_PORT, HC_SR04_TRIG_PIN);
    ok_bit = 1;
}

float Ultrasonic_Read(void)
{
    float dis = 0;
    for (int i = 0; i < 10; i++)
    {
        Ultrasonic_Start();
        while (ok_bit);
        dis += distance;
    }
    dis /= 10.0;
    return dis * SOUND_SPEED / 2 * 100;
}
