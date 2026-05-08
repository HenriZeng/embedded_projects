/**
  ******************************************************************************
  * @file           : pwm_app.h
  * @brief          : PWM Application Layer Header
  * @author         : Smart Control Console Team
  * @version        : V0.2
  ******************************************************************************
  * @attention
  *
  * This module provides high-level PWM control functions for motor/LED
  * brightness control with percentage-based duty cycle setting.
  *
  ******************************************************************************
  */

#ifndef __PWM_APP_H
#define __PWM_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define PWM_ADC_MAX         4095    // Maximum ADC value for mapping

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/**
  * @brief  Initialize PWM application module
  * @param  htim: pointer to TIM handle
  * @param  channel: TIM channel (e.g., TIM_CHANNEL_1)
  * @retval None
  */
void PWM_App_Init(TIM_HandleTypeDef *htim, uint32_t channel);

/**
  * @brief  Start PWM output
  * @retval None
  */
void PWM_App_Start(void);

/**
  * @brief  Stop PWM output
  * @retval None
  */
void PWM_App_Stop(void);

/**
  * @brief  Set PWM duty cycle by percentage
  * @param  percent: Duty cycle percentage (0-100)
  * @retval None
  */
void PWM_App_SetDuty(uint8_t percent);

/**
  * @brief  Set PWM duty cycle by raw ADC value
  * @param  adc_value: Raw ADC value (0-4095)
  * @retval None
  */
void PWM_App_SetFromADC(uint32_t adc_value);

/**
  * @brief  Get current PWM duty cycle percentage
  * @retval Current duty cycle percentage (0-100)
  */
uint8_t PWM_App_GetDuty(void);

#ifdef __cplusplus
}
#endif

#endif /* __PWM_APP_H */
