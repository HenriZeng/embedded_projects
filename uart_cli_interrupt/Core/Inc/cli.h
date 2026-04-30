#ifndef __CLI_H
#define __CLI_H

#include "main.h"

void CLI_Init(UART_HandleTypeDef *huart);
void CLI_InputChar(uint8_t ch);

#endif
