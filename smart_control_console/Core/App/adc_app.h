/**
  ******************************************************************************
  * @file           : adc_app.h
  * @brief          : ADC Application Layer Header
  * @author         : Smart Control Console Team
  * @version        : V0.2
  ******************************************************************************
  * @attention
  *
  * This module provides high-level ADC reading functions with automatic
  * conversion to voltage and percentage values.
  *
  ******************************************************************************
  */

#ifndef __ADC_APP_H
#define __ADC_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define ADC_VREF_MV         3300    // Reference voltage in millivolts
#define ADC_RESOLUTION      4095    // 12-bit ADC resolution

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/**
  * @brief  Initialize ADC application module
  * @param  hadc: pointer to ADC handle
  * @retval None
  */
void ADC_App_Init(ADC_HandleTypeDef *hadc);

/**
  * @brief  Read raw ADC value (0-4095)
  * @retval Raw ADC value
  */
uint32_t ADC_App_ReadRaw(void);

/**
  * @brief  Read ADC value converted to millivolts
  * @retval Voltage in millivolts (0-3300)
  */
uint32_t ADC_App_ReadMV(void);

/**
  * @brief  Read ADC value converted to percentage
  * @retval Percentage value (0-100)
  */
uint32_t ADC_App_ReadPercent(void);

#ifdef __cplusplus
}
#endif

#endif /* __ADC_APP_H */
