/**
  ******************************************************************************
  * @file           : pwm_app.c
  * @brief          : PWM Application Layer Implementation
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

/* Includes ------------------------------------------------------------------*/
#include "pwm_app.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TIM_HandleTypeDef *htim_pwm = NULL;
static uint32_t pwm_channel = 0;
static uint32_t pwm_max_value = 0;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/**
  * @brief  Initialize PWM application module
  * @param  htim: pointer to TIM handle
  * @param  channel: TIM channel (e.g., TIM_CHANNEL_1)
  * @retval None
  */
void PWM_App_Init(TIM_HandleTypeDef *htim, uint32_t channel)
{
    htim_pwm = htim;
    pwm_channel = channel;
    
    // Get ARR value (Period) to calculate max PWM value
    pwm_max_value = __HAL_TIM_GET_AUTORELOAD(htim_pwm);
}

/**
  * @brief  Start PWM output
  * @retval None
  */
void PWM_App_Start(void)
{
    if (htim_pwm != NULL)
    {
        HAL_TIM_PWM_Start(htim_pwm, pwm_channel);
    }
}

/**
  * @brief  Stop PWM output
  * @retval None
  */
void PWM_App_Stop(void)
{
    if (htim_pwm != NULL)
    {
        HAL_TIM_PWM_Stop(htim_pwm, pwm_channel);
    }
}

/**
  * @brief  Set PWM duty cycle by percentage
  * @param  percent: Duty cycle percentage (0-100)
  * @retval None
  */
void PWM_App_SetDuty(uint8_t percent)
{
    if (htim_pwm == NULL)
    {
        return;
    }
    
    // Limit to 0-100%
    if (percent > 100)
    {
        percent = 100;
    }
    
    // Calculate compare value
    uint32_t compare_value = (pwm_max_value * percent) / 100;
    
    // Set PWM duty cycle
    __HAL_TIM_SET_COMPARE(htim_pwm, pwm_channel, compare_value);
}

/**
  * @brief  Set PWM duty cycle by raw ADC value
  * @param  adc_value: Raw ADC value (0-4095)
  * @retval None
  */
void PWM_App_SetFromADC(uint32_t adc_value)
{
    if (htim_pwm == NULL)
    {
        return;
    }
    
    // Map ADC value (0-4095) to PWM compare value
    uint32_t compare_value = (pwm_max_value * adc_value) / PWM_ADC_MAX;
    
    // Set PWM duty cycle
    __HAL_TIM_SET_COMPARE(htim_pwm, pwm_channel, compare_value);
}

/**
  * @brief  Get current PWM duty cycle percentage
  * @retval Current duty cycle percentage (0-100)
  */
uint8_t PWM_App_GetDuty(void)
{
    if (htim_pwm == NULL)
    {
        return 0;
    }
    
    uint32_t compare_value = __HAL_TIM_GET_COMPARE(htim_pwm, pwm_channel);
    return (uint8_t)((compare_value * 100) / pwm_max_value);
}
