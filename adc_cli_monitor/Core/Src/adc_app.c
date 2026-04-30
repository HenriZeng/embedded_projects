#include "adc_app.h"
#include <stdio.h>
#include <string.h>

static ADC_HandleTypeDef *adc;
static UART_HandleTypeDef *uart;

void ADC_App_Init(ADC_HandleTypeDef *hadc, UART_HandleTypeDef *huart)
{
    adc = hadc;
    uart = huart;
}

void ADC_PrintOnce(void)
{
    uint32_t adc_val;
    char msg[64];

    HAL_ADC_PollForConversion(adc, HAL_MAX_DELAY);
    adc_val = HAL_ADC_GetValue(adc);

    uint32_t voltage_mv = adc_val * 3300 / 4095;

    sprintf(msg, "ADC=%lu  V=%lumV\r\n", adc_val, voltage_mv);
    HAL_UART_Transmit(uart, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
}
