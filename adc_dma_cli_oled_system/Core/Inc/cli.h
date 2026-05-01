#ifndef __CLI_H
#define __CLI_H

#include "main.h"

typedef enum
{
    MODE_STOP = 0,
    MODE_STREAM = 1
} SystemMode;

extern volatile SystemMode system_mode;
extern volatile uint8_t read_once;
extern volatile uint32_t read_flash_until;

void CLI_Init(UART_HandleTypeDef *huart);
void CLI_InputChar(uint8_t ch);

#endif
