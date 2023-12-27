#ifndef __JAMIEXU_BLUETOOTH_H_
#define __JAMIEXU_BLUETOOTH_H_
#include "stm32f10x.h"
#include "string.h"
#include "stdio.h"
#include "car.h"
#include "delay.h"

typedef enum
{
    CONNECT = 0,
    DISCONNECT = 1,
    OPERATION = 2,
    HEART = 3
} InfoType;

extern u8 cmdData[255];
extern u8 pos;

void Bluetooth_Proc(void);

void Bluetooth_Send(u16 type, u8 *cmd);

#endif
