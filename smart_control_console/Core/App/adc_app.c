/**
  ******************************************************************************
  * @file           : adc_app.c
  * @brief          : ADC Application Layer Implementation
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

/* Includes ------------------------------------------------------------------*/
#include "adc_app.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static ADC_HandleTypeDef *hadc_app = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/**
  * @brief  Initialize ADC application module
  * @param  hadc: pointer to ADC handle
  * @retval None
  */
void ADC_App_Init(ADC_HandleTypeDef *hadc)
{
    hadc_app = hadc;
}

/**
  * @brief  Read raw ADC value (0-4095)
  * @retval Raw ADC value
  */
uint32_t ADC_App_ReadRaw(void)
{
    uint32_t adc_value = 0;
    
    if (hadc_app == NULL)
    {
        return 0;
    }
    
    HAL_ADC_Start(hadc_app);
    
    if (HAL_ADC_PollForConversion(hadc_app, 100) == HAL_OK)
    {
        adc_value = HAL_ADC_GetValue(hadc_app);
    }
    
    HAL_ADC_Stop(hadc_app);
    
    return adc_value;
}

/**
  * @brief  Read ADC value converted to millivolts
  * @retval Voltage in millivolts (0-3300)
  */
uint32_t ADC_App_ReadMV(void)
{
    uint32_t raw = ADC_App_ReadRaw();
    return (raw * ADC_VREF_MV) / ADC_RESOLUTION;
}

/**
  * @brief  Read ADC value converted to percentage
  * @retval Percentage value (0-100)
  */
uint32_t ADC_App_ReadPercent(void)
{
    uint32_t raw = ADC_App_ReadRaw();
    return (raw * 100) / ADC_RESOLUTION;
}
