#ifndef __JAMIEXU_MAIN_H_
#define __JAMIEXU_MAIN_H_
#include "stm32f10x.h"
#include "delay.h"
#include "gpio.h"
#include "nvic.h"
#include "timer.h"
#include "usart.h"
#include "exti.h"
#include "ultrasonicwave.h"

#define KEY_LT_READ GPIO_ReadInputDataBit(KEY_LT_PORT, KEY_LT_PIN)
#define KEY_MD_READ GPIO_ReadInputDataBit(KEY_MD_PORT, KEY_MD_PIN)
#define KEY_RT_READ GPIO_ReadInputDataBit(KEY_RT_PORT, KEY_RT_PIN)

#define LED_RED_ON LED_RED_PORT->BRR = LED_RED_PIN
#define LED_RED_OFF LED_RED_PORT->BSRR = LED_RED_PIN
#define LED_RED_TOGGLE LED_RED_PORT->ODR ^= LED_RED_PIN

// #define LED_GREEN_ON LED_GREEN_PORT->BRR = LED_GREEN_PIN
// #define LED_GREEN_OFF LED_GREEN_PORT->BSRR = LED_GREEN_PIN
// #define LED_GREEN_TOGGLE LED_GREEN_PORT->ODR ^= LED_GREEN_PIN

// #define LED_BLUE_ON LED_BLUE_PORT->BRR = LED_BLUE_PIN
// #define LED_BLUE_OFF LED_BLUE_PORT->BSRR = LED_BLUE_PIN
// #define LED_BLUE_TOGGLE LED_BLUE_PORT->ODR ^= LED_RED_PIN

#define BELL_ON BELL_PORT->BRR = BELL_PIN
#define BELL_OFF BELL_PORT->BSRR = BELL_PIN

extern u8 ok_bit;

#endif
