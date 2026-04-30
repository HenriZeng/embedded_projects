#include "cli.h"
#include <string.h>
#include <stdio.h>

static UART_HandleTypeDef *cli_uart;

static char rx_buf[64];
static uint8_t rx_index = 0;

/* ================= 命令函数 ================= */

static void cmd_on(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_UART_Transmit(cli_uart, (uint8_t *)"LED ON\r\n", 8, HAL_MAX_DELAY);
}

static void cmd_off(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_UART_Transmit(cli_uart, (uint8_t *)"LED OFF\r\n", 9, HAL_MAX_DELAY);
}

static void cmd_status(void)
{
    GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);

    if (state == GPIO_PIN_SET)
    {
        HAL_UART_Transmit(cli_uart, (uint8_t *)"LED=ON\r\n", 8, HAL_MAX_DELAY);
    }
    else
    {
        HAL_UART_Transmit(cli_uart, (uint8_t *)"LED=OFF\r\n", 9, HAL_MAX_DELAY);
    }
}

static void cmd_help(void)
{
    char msg[] =
        "\r\nCommands:\r\n"
        "ON      - Turn LED ON\r\n"
        "OFF     - Turn LED OFF\r\n"
        "STATUS  - Show LED state\r\n"
        "HELP    - Show this message\r\n";

    HAL_UART_Transmit(cli_uart, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
}

/* ================= 命令表 ================= */

typedef struct
{
    const char *cmd;
    void (*handler)(void);
} CLI_Command;

static CLI_Command cmd_table[] =
{
    {"ON",     cmd_on},
    {"OFF",    cmd_off},
    {"STATUS", cmd_status},
    {"HELP",   cmd_help},
};

/* ================= 初始化 ================= */

void CLI_Init(UART_HandleTypeDef *huart)
{
    cli_uart = huart;

    char msg[] = "UART CLI Ready\r\n> ";
    HAL_UART_Transmit(cli_uart, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
}

/* ================= 输入处理 ================= */

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

void CLI_InputChar(uint8_t ch)
{
    /* ---------- 回车处理 ---------- */
    if (ch == '\r' || ch == '\n')
    {
        rx_buf[rx_index] = '\0';

        str_to_upper(rx_buf);

        if (rx_index > 0)
        {
            /* 转大写（支持小写命令） */
            for (int i = 0; i < rx_index; i++)
            {
                if (rx_buf[i] >= 'a' && rx_buf[i] <= 'z')
                {
                    rx_buf[i] -= 32;
                }
            }

            int found = 0;

            for (int i = 0; i < sizeof(cmd_table) / sizeof(cmd_table[0]); i++)
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
                HAL_UART_Transmit(cli_uart, (uint8_t *)"Unknown CMD\r\n", 13, HAL_MAX_DELAY);
            }
        }

        /* 重置缓冲区 */
        rx_index = 0;
        memset(rx_buf, 0, sizeof(rx_buf));

        /* 提示符 */
        HAL_UART_Transmit(cli_uart, (uint8_t *)"> ", 2, HAL_MAX_DELAY);
    }

    /* ---------- 退格支持 ---------- */
    else if (ch == 0x08 || ch == 0x7F)
    {
        if (rx_index > 0)
        {
            rx_index--;
        }
    }

    /* ---------- 普通字符 ---------- */
    else
    {
        if (rx_index < sizeof(rx_buf) - 1)
        {
            rx_buf[rx_index++] = ch;
        }
    }
}
