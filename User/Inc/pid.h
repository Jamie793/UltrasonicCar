#ifndef __JAMIEXU_PID_H_
#define __JAMIEXU_PID_H_
#include "stm32f10x.h"
#include "car.h"
#define PIDDEBUG_PACKAGET_HEADER 0x59485A53 
// #define PIDDEBUG_PACKAGET_HEADER 0x535A4859 

extern float pid_actual[4];
extern float pid_err[4];
extern float pid_err2[4];
extern float pid_err3[4];
extern float pid_duk[4];
extern float Kp, Ki, Kd;
void PIDDebug_Set_Actual(u8 channel, u32 value);

void PIDDebug_Set_Target(u8 channel, u32 value);

void PIDDebug_Proc(u8 *buffer);

u8 PIDDebug_Calc(u8 *buffer, u32 size);

u8 PIDDebug_Check(u8 *buffer, u32 size);

void PIDCar_Init(void);

void PIDCar_Speed_A(u32 target);

#endif
