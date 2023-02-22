#ifndef __JAMIEXU_ULTRASONICWAVE_H_
#define __JAMIEXU_ULTRASONICWAVE_H_
#include "stm32f10x.h"
#include "main.h"
#include "gpio.h"
#include "delay.h"

#define SOUND_SPEED 340
#define ECHO_READ GPIO_ReadInputDataBit(HC_SR04_ECHO_PORT, HC_SR04_ECHO_PIN)


extern float distance;


void Ultrasonic_Start(void);

float Ultrasonic_Read(void);

#endif
