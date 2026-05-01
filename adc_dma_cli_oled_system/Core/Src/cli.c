#include "cli.h"
#include <string.h>
#include <stdio.h>

static UART_HandleTypeDef *cli_uart;

static char rx_buf[64];
static uint8_t rx_index = 0;

uint8_t streaming = 0;

static void send_str(const char *s)
{
    HAL_UART_Transmit(cli_uart, (uint8_t*)s, strlen(s), HAL_MAX_DELAY);
}

static void str_to_upper(char *str)
{
    while (*str)
    {
        if (*str >= 'a' && *str <= 'z')
            *str -= 32;
        str++;
    }
}

static void cmd_read(void)
{
    streaming = 0;
    send_str("READ ONCE\r\n");
}

static void cmd_stream(void)
{
    streaming = 1;
    send_str("STREAM ON\r\n");
}

static void cmd_stop(void)
{
    streaming = 0;
    send_str("STREAM OFF\r\n");
}

static void cmd_help(void)
{
    send_str(
        "\r\nCommands:\r\n"
        "READ\r\n"
        "STREAM\r\n"
        "STOP\r\n"
        "HELP\r\n");
}

typedef struct {
    const char *cmd;
    void (*handler)(void);
} CLI_Command;

static CLI_Command cmd_table[] =
{
    {"READ",   cmd_read},
    {"STREAM", cmd_stream},
    {"STOP",   cmd_stop},
    {"HELP",   cmd_help},
};

void CLI_Init(UART_HandleTypeDef *huart)
{
    cli_uart = huart;
    send_str("CLI READY\r\n> ");
}

void CLI_InputChar(uint8_t ch)
{
    if (ch == '\r' || ch == '\n')
    {
        rx_buf[rx_index] = '\0';

        if (rx_index > 0)
        {
            str_to_upper(rx_buf);

            uint8_t found = 0;

            for (uint8_t i = 0; i < sizeof(cmd_table)/sizeof(cmd_table[0]); i++)
            {
                if (strcmp(rx_buf, cmd_table[i].cmd) == 0)
                {
                    cmd_table[i].handler();
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                send_str("Unknown CMD\r\n");
            }
        }

        rx_index = 0;
        memset(rx_buf, 0, sizeof(rx_buf));
        send_str("> ");
    }
    else if (ch == 0x08 || ch == 0x7F)
    {
        if (rx_index > 0) rx_index--;
    }
    else
    {
        if (rx_index < sizeof(rx_buf)-1)
        {
            rx_buf[rx_index++] = ch;
        }
    }
}
