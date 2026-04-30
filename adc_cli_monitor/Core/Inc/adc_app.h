#ifndef __ADC_APP_H
#define __ADC_APP_H

#include "main.h"

void ADC_App_Init(ADC_HandleTypeDef *hadc, UART_HandleTypeDef *huart);
void ADC_PrintOnce(void);

#endif
