#ifndef __JAMIEXU_GPIO_H_
#define __JAMIEXU_GPIO_H_
#include "stm32f10x.h"

#define HC_SR04_TRIG_PORT GPIOA
#define HC_SR04_TRIG_PIN GPIO_Pin_1
#define HC_SR04_ECHO_PORT GPIOA
#define HC_SR04_ECHO_PIN GPIO_Pin_0
#define HC_SR04_ECHO_PORT_SOURCE GPIO_PortSourceGPIOA
#define HC_SR04_ECHO_PIN_SOURCE GPIO_PinSource0


#define USART1_PORT GPIOA
#define USART1_TX_PIN GPIO_Pin_9
#define USART1_RX_PIN GPIO_Pin_10




#define KEY_LT_PORT GPIOB
#define KEY_LT_PIN GPIO_Pin_13

#define KEY_MD_PORT GPIOB
#define KEY_MD_PIN GPIO_Pin_15

#define KEY_RT_PORT GPIOA
#define KEY_RT_PIN GPIO_Pin_11




#define LED_RED_PORT GPIOA
#define LED_RED_PIN GPIO_Pin_2

// #define LED_GREEN_PORT GPIOA
// #define LED_GREEN_PIN GPIO_Pin_4

// #define LED_BLUE_PORT GPIOA
// #define LED_BLUE_PIN GPIO_Pin_6

#define BELL_PORT GPIOB
#define BELL_PIN GPIO_Pin_12

#define LDR_PORT GPIOB
#define LDR_PIN GPIO_Pin_11




#define MOTOR_A_IN1_PORT GPIOC
#define MOTOR_A_IN1_PIN GPIO_Pin_15

#define MOTOR_A_IN2_PORT GPIOC
#define MOTOR_A_IN2_PIN GPIO_Pin_14

#define MOTOR_A_PWM_PORT GPIOA
#define MOTOR_A_PWM_PIN GPIO_Pin_6


#define MOTOR_B_IN1_PORT GPIOA
#define MOTOR_B_IN1_PIN GPIO_Pin_5

#define MOTOR_B_IN2_PORT GPIOC
#define MOTOR_B_IN2_PIN GPIO_Pin_13

#define MOTOR_B_PWM_PORT GPIOA
#define MOTOR_B_PWM_PIN GPIO_Pin_7


#define MOTOR_C_IN1_PORT GPIOC
#define MOTOR_C_IN1_PIN GPIO_Pin_15

#define MOTOR_C_IN2_PORT GPIOC
#define MOTOR_C_IN2_PIN GPIO_Pin_14

#define MOTOR_C_PWM_PORT GPIOB
#define MOTOR_C_PWM_PIN GPIO_Pin_0


#define MOTOR_D_IN1_PORT GPIOC
#define MOTOR_D_IN1_PIN GPIO_Pin_15

#define MOTOR_D_IN2_PORT GPIOC
#define MOTOR_D_IN2_PIN GPIO_Pin_14

#define MOTOR_D_PWM_PORT GPIOA
#define MOTOR_D_PWM_PIN GPIO_Pin_6



void GPIOx_Init(void);

void LED_GPIO_Init(void);

void KEY_GPIO_Init(void);

void BELL_GPIO_Init(void);

void LDR_GPIO_Init(void);

void HC_SR04_GPIO_Init(void);

void USART1_GPIO_Init(void);

void MOTOR_GPIO_Init(void);

#endif
