#include "adc_app.h"

static ADC_HandleTypeDef *adc;

void ADC_App_Init(ADC_HandleTypeDef *hadc)
{
    adc = hadc;
}

uint32_t ADC_ReadRaw(void)
{
    HAL_ADC_Start(adc);
    HAL_ADC_PollForConversion(adc, HAL_MAX_DELAY);
    return HAL_ADC_GetValue(adc);
}

uint32_t ADC_ReadVoltageMv(void)
{
    uint32_t raw = ADC_ReadRaw();
    return raw * 3300 / 4095;
}
