#ifndef __ADC_APP_H
#define __ADC_APP_H

#include "main.h"

void ADC_App_Init(ADC_HandleTypeDef *hadc);
uint32_t ADC_ReadRaw(void);
uint32_t ADC_ReadVoltageMv(void);

#endif
