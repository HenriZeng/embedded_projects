#include "cli.h"
#include "adc_app.h"
#include <string.h>

extern volatile uint8_t streaming;

static UART_HandleTypeDef *cli_uart;
static char rx_buf[32];
static uint8_t rx_index = 0;

static void str_to_upper(char *str)
{
    while (*str)
    {
        if (*str >= 'a' && *str <= 'z')
        {
            *str -= 32;
        }
        str++;
    }
}

void CLI_Init(UART_HandleTypeDef *huart)
{
    cli_uart = huart;

    char msg[] = "ADC CLI Monitor Ready\r\nType HELP\r\n> ";
    HAL_UART_Transmit(cli_uart, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
}

void CLI_InputChar(uint8_t ch)
{
    if (ch == '\r' || ch == '\n')
    {
        rx_buf[rx_index] = '\0';

        if (rx_index > 0)
        {
            str_to_upper(rx_buf);

            if (strcmp(rx_buf, "READ") == 0)
            {
                ADC_PrintOnce();
            }
            else if (strcmp(rx_buf, "STREAM") == 0)
            {
                streaming = 1;
                HAL_UART_Transmit(cli_uart, (uint8_t *)"STREAM ON\r\n", 11, HAL_MAX_DELAY);
            }
            else if (strcmp(rx_buf, "STOP") == 0)
            {
                streaming = 0;
                HAL_UART_Transmit(cli_uart, (uint8_t *)"STREAM OFF\r\n", 12, HAL_MAX_DELAY);
            }
            else if (strcmp(rx_buf, "HELP") == 0)
            {
                char msg[] =
                    "Commands:\r\n"
                    "READ   - Read ADC once\r\n"
                    "STREAM - Start continuous ADC output\r\n"
                    "STOP   - Stop continuous ADC output\r\n"
                    "HELP   - Show this message\r\n";

                HAL_UART_Transmit(cli_uart, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
            }
            else
            {
                HAL_UART_Transmit(cli_uart, (uint8_t *)"Unknown CMD\r\n", 13, HAL_MAX_DELAY);
            }
        }

        rx_index = 0;
        memset(rx_buf, 0, sizeof(rx_buf));
        HAL_UART_Transmit(cli_uart, (uint8_t *)"> ", 2, HAL_MAX_DELAY);
    }
    else if (ch == 0x08 || ch == 0x7F)
    {
        if (rx_index > 0)
        {
            rx_index--;
        }
    }
    else
    {
        if (rx_index < sizeof(rx_buf) - 1)
        {
            rx_buf[rx_index++] = ch;
        }
    }
}
