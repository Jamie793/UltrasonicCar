#include "pid.h"
u8 buffer[100];
float pid_actual[4];
float pid_err[4];
float pid_err2[4];
float pid_err3[4];
float pid_duk[4];
float Kp, Ki, Kd;

void PIDDebug_Set_Actual(u8 channel, u32 value)
{
    *(u32 *)(buffer) = PIDDEBUG_PACKAGET_HEADER;
    buffer[4] = channel;
    *(u32 *)(buffer + 5) = 0x0F;
    buffer[9] = 0x02;
    *(u32 *)(buffer + 10) = value;
    buffer[14] = PIDDebug_Calc(buffer, 0x0F - 1);
    USART1_SendBytes(buffer, 0x0F);
}

void PIDDebug_Set_Target(u8 channel, u32 value)
{
    *(u32 *)(buffer) = PIDDEBUG_PACKAGET_HEADER;
    buffer[4] = channel;
    *(u32 *)(buffer + 5) = 0x0F;
    buffer[9] = 0x01;
    *(u32 *)(buffer + 10) = value;
    buffer[14] = PIDDebug_Calc(buffer, 0x0F - 1);
    USART1_SendBytes(buffer, 0x0F);
}

void PIDDebug_Proc(u8 *buffer)
{
    u8 channel = buffer[4];
    u32 size = *(u32 *)(buffer + 4);
    u8 cmd = buffer[9];
    float p = *(float *)(buffer + 10);
    float i = *(float *)(buffer + 14);
    float d = *(float *)(buffer + 18);

    Kp = p;
    Ki = i;
    Kd = d;
}

u8 PIDDebug_Calc(u8 *buffer, u32 size)
{
    u8 v = 0;
    while (size--)
    {
        v += *buffer;
        buffer++;
    }
    return v;
}

void PIDCar_Init(void)
{
    u8 i;
    Kp = 5;
    Ki = 0;
    Kd = 0;
    for (i = 0; i < 4; i++)
    {
        pid_actual[i] = 0;
        pid_err[i] = 0;
        pid_err2[i] = 0;
        pid_err3[i] = 0;
        pid_duk[i] = 0;
    }
}

void PIDCar_Speed_A(u32 target)
{
    float duk;
    float out;
    pid_err[0] = target - pid_actual[0];
    // printf("err: %.2f, last_err: %.2f\n", pid_err[0], pid_err2[0]);
    duk = Kp * (pid_err[0] - pid_err2[0]) + (Ki * pid_err[0]) + (Kd * (pid_err[0] - 2 * pid_err2[0] + pid_err3[0]));
    duk += pid_duk[0];
    pid_err3[0] = pid_err2[0];
    pid_err2[0] = pid_err[0];
    pid_duk[0] = duk;
    out = (int)(duk);
    printf("duk: %.2f\n", out);
    if (out >= 1000 - 1)
        Car_PWM_Set(1000 - 1);
    else if (out <= 0)
        Car_PWM_Set(0);
    else
        Car_PWM_Set(out);
}