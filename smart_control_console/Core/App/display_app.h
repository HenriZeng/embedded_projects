/**
  ******************************************************************************
  * @file           : display_app.h
  * @brief          : Display Application Layer Header
  * @author         : Smart Control Console Team
  * @version        : V0.2
  ******************************************************************************
  * @attention
  *
  * This module provides high-level display functions for OLED screen
  * with formatted data presentation.
  *
  ******************************************************************************
  */

#ifndef __DISPLAY_APP_H
#define __DISPLAY_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/**
  * @brief  Initialize display application module
  * @retval None
  */
void Display_App_Init(void);

/**
  * @brief  Update display with sensor and control data
  * @param  adc: Raw ADC value (0-4095)
  * @param  mv: Voltage in millivolts
  * @param  pwm_percent: PWM duty cycle percentage (0-100)
  * @retval None
  */
void Display_App_Update(uint32_t adc, uint32_t mv, uint32_t pwm_percent);

/**
  * @brief  Display error message
  * @param  error_msg: Error message string (max 20 chars)
  * @retval None
  */
void Display_App_ShowError(const char *error_msg);

/**
  * @brief  Display custom message
  * @param  line1: First line text
  * @param  line2: Second line text
  * @param  line3: Third line text
  * @param  line4: Fourth line text
  * @retval None
  */
void Display_App_ShowMessage(const char *line1, const char *line2, 
                              const char *line3, const char *line4);

/**
  * @brief  Clear display screen
  * @retval None
  */
void Display_App_Clear(void);

#ifdef __cplusplus
}
#endif

#endif /* __DISPLAY_APP_H */
