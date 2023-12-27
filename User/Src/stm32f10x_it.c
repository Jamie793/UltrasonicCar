/**
 ******************************************************************************
 * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c
 * @author  MCD Application Team
 * @version V3.5.0
 * @date    08-April-2011
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "main.h"
#include "string.h"
#include "ultrasonicwave.h"
#include "bluetooth.h"
#include "car.h"
#include "pid.h"
/** @addtogroup STM32F10x_StdPeriph_Template
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
 * @brief  This function handles PPP interrupt request.
 * @param  None
 * @retval None
 */
/*void PPP_IRQHandler(void)
{
}*/

/**
 * @}
 */

u32 time = 0;
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        // distance++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        if (++time >= 20)
        {
            pid_actual[0] = (pid_actual[0] / 20.0) * (60000 / 20);
            // pid_actual[1] = pid_actual[1] / 20.0;
            // pid_actual[2] = pid_actual[2] / 20.0;
            // pid_actual[3] = pid_actual[3] / 20.0;
            // printf("Motor Speed A: %d RPM\nMotor Speed B: %d RPM\nMotor Speed C: %d RPM\nMotor Speed D: %d RPM\nSpeed: %.2fm/s\n\n",
            //        (u32)pid_actual[0],
            //        (u32)pid_actual[1],
            //        (u32)pid_actual[2],
            //        (u32)pid_actual[3],
            //        pid_actual[0] / 60 * 2 * 3.14 * 0.048);
            PIDDebug_Set_Actual(1, (u32)pid_actual[0]);
            // PIDDebug_Set_Target(1, 100);
            PIDCar_Speed_A(100);
            pid_actual[0] = 0;
            pid_actual[1] = 0;
            pid_actual[2] = 0;
            pid_actual[3] = 0;
            time = 0;
        }
    }
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        TIM_SetCounter(TIM2, 0);
        TIM_Cmd(TIM2, ENABLE);
        while (ECHO_READ)
            ;
        TIM_Cmd(TIM2, DISABLE);
        distance = TIM_GetCounter(TIM2) * 1e-6;
        ok_bit = 0;
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);

        u16 data = USART_ReceiveData(USART1);
        // USART_SendData(USART1, data);
        cmdData[pos++] = data;
        // if (cmdData[pos - 2] == 0x05 && cmdData[pos - 1] == 0x02)
        // {
        //     pos = 2;
        //     memset(cmdData + 2, 0, 255);
        // }
        // else if (cmdData[pos - 2] == 0x05 && cmdData[pos - 1] == 0x04)
        // {
        //     Bluetooth_Proc();
        // }
        if (cmdData[0] == 0x53 && cmdData[1] == 0x5A && cmdData[2] == 0x48 && cmdData[3] == 0x59 && pos >= 0x17)
        {
            PIDDebug_Proc(cmdData);
            pos = 0;
        }
    }
}

void DMA1_Channel5_IRQHandler(void)
{
    if (DMA_GetITStatus(DMA1_IT_TC5) != RESET)
    {
        // pos = MAX_RECEIVE_SIZE - DMA_GetCurrDataCounter(DMA1_Channel5);
        // if (cmdData[pos - 2] == 0x05 && cmdData[pos - 1] == 0x02)
        // {
        //     DMA_Cmd(DMA1_Channel5, DISABLE);
        //     DMA_SetCurrDataCounter(DMA1_Channel5, MAX_RECEIVE_SIZE);
        //     DMA_Cmd(DMA1_Channel5, ENABLE);
        //     memset(cmdData, 0, 255);
        // }
        // else if (cmdData[pos - 2] == 0x05 && cmdData[pos - 1] == 0x04)
        // {
        //     dataSize = 0;
        //     dataSize |= cmdData[4];
        //     dataSize |= cmdData[3] << 8;
        //     printf("size: %d", dataSize);
        // }
        // if (cmdData[0] == 0x05 && cmdData[1] == 0x02)
        // {
        DMA_Cmd(DMA1_Channel5, DISABLE);
        DMA_SetCurrDataCounter(DMA1_Channel5, MAX_RECEIVE_SIZE);
        DMA_Cmd(DMA1_Channel5, ENABLE);
        // }
        DMA_ClearITPendingBit(DMA1_IT_TC5);
    }
}

void EXTI9_5_IRQHandler(void)
{

    if (EXTI_GetITStatus(EXTI_Line5) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line5);
        pid_actual[0]++;
    }

    if (EXTI_GetITStatus(EXTI_Line6) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line6);
        pid_actual[1]++;
    }

    if (EXTI_GetITStatus(EXTI_Line7) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line7);
        pid_actual[2]++;
    }

    if (EXTI_GetITStatus(EXTI_Line8) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line8);
        pid_actual[3]++;
    }
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
