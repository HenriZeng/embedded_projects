#include "ssd1306.h"
#include <string.h>

extern I2C_HandleTypeDef hi2c1;

#define SSD1306_ADDR 0x78
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

static uint8_t buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

static void SSD1306_WriteCommand(uint8_t cmd)
{
    uint8_t data[2] = {0x00, cmd};
    HAL_I2C_Master_Transmit(&hi2c1, SSD1306_ADDR, data, 2, HAL_MAX_DELAY);
}

static void SSD1306_WriteData(uint8_t *data, uint16_t size)
{
    uint8_t temp[129];
    temp[0] = 0x40;

    while (size)
    {
        uint16_t chunk = size > 128 ? 128 : size;
        memcpy(&temp[1], data, chunk);
        HAL_I2C_Master_Transmit(&hi2c1, SSD1306_ADDR, temp, chunk + 1, HAL_MAX_DELAY);
        data += chunk;
        size -= chunk;
    }
}

void SSD1306_Init(void)
{
    HAL_Delay(100);

    SSD1306_WriteCommand(0xAE);
    SSD1306_WriteCommand(0x20);
    SSD1306_WriteCommand(0x00);
    SSD1306_WriteCommand(0xB0);
    SSD1306_WriteCommand(0xC8);
    SSD1306_WriteCommand(0x00);
    SSD1306_WriteCommand(0x10);
    SSD1306_WriteCommand(0x40);
    SSD1306_WriteCommand(0x81);
    SSD1306_WriteCommand(0x7F);
    SSD1306_WriteCommand(0xA1);
    SSD1306_WriteCommand(0xA6);
    SSD1306_WriteCommand(0xA8);
    SSD1306_WriteCommand(0x3F);
    SSD1306_WriteCommand(0xA4);
    SSD1306_WriteCommand(0xD3);
    SSD1306_WriteCommand(0x00);
    SSD1306_WriteCommand(0xD5);
    SSD1306_WriteCommand(0x80);
    SSD1306_WriteCommand(0xD9);
    SSD1306_WriteCommand(0xF1);
    SSD1306_WriteCommand(0xDA);
    SSD1306_WriteCommand(0x12);
    SSD1306_WriteCommand(0xDB);
    SSD1306_WriteCommand(0x40);
    SSD1306_WriteCommand(0x8D);
    SSD1306_WriteCommand(0x14);
    SSD1306_WriteCommand(0xAF);
}

void SSD1306_Clear(void)
{
    memset(buffer, 0x00, sizeof(buffer));
}

void SSD1306_Fill(void)
{
    memset(buffer, 0xFF, sizeof(buffer));
}

void SSD1306_UpdateScreen(void)
{
    for (uint8_t page = 0; page < 8; page++)
    {
        SSD1306_WriteCommand(0xB0 + page);
        SSD1306_WriteCommand(0x00);
        SSD1306_WriteCommand(0x10);
        SSD1306_WriteData(&buffer[SSD1306_WIDTH * page], SSD1306_WIDTH);
    }
}

static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

void SSD1306_DrawPixel(uint8_t x, uint8_t y, uint8_t color)
{
    if (x >= 128 || y >= 64) return;

    if (color)
        buffer[x + (y / 8) * 128] |= (1 << (y % 8));
    else
        buffer[x + (y / 8) * 128] &= ~(1 << (y % 8));
}

void SSD1306_SetCursor(uint8_t x, uint8_t y)
{
    cursor_x = x;
    cursor_y = y;
}

static const uint8_t* get_char_bitmap(char c)
{
    static const uint8_t space[5] = {0x00,0x00,0x00,0x00,0x00};
    static const uint8_t A[5] = {0x7E,0x11,0x11,0x11,0x7E};
    static const uint8_t C[5] = {0x3E,0x41,0x41,0x41,0x22};
    static const uint8_t D[5] = {0x7F,0x41,0x41,0x22,0x1C};
    static const uint8_t V[5] = {0x1F,0x20,0x40,0x20,0x1F};
    static const uint8_t m[5] = {0x7C,0x04,0x18,0x04,0x78};
    static const uint8_t colon[5] = {0x00,0x36,0x36,0x00,0x00};
    static const uint8_t n0[5] = {0x3E,0x51,0x49,0x45,0x3E};
    static const uint8_t n1[5] = {0x00,0x42,0x7F,0x40,0x00};
    static const uint8_t n2[5] = {0x42,0x61,0x51,0x49,0x46};
    static const uint8_t n3[5] = {0x21,0x41,0x45,0x4B,0x31};
    static const uint8_t n4[5] = {0x18,0x14,0x12,0x7F,0x10};
    static const uint8_t n5[5] = {0x27,0x45,0x45,0x45,0x39};
    static const uint8_t n6[5] = {0x3C,0x4A,0x49,0x49,0x30};
    static const uint8_t n7[5] = {0x01,0x71,0x09,0x05,0x03};
    static const uint8_t n8[5] = {0x36,0x49,0x49,0x49,0x36};
    static const uint8_t n9[5] = {0x06,0x49,0x49,0x29,0x1E};
    static const uint8_t E[5] = {0x7F,0x49,0x49,0x49,0x41};
    static const uint8_t M[5] = {0x7F,0x02,0x0C,0x02,0x7F};
    static const uint8_t O[5] = {0x3E,0x41,0x41,0x41,0x3E};
    static const uint8_t P[5] = {0x7F,0x09,0x09,0x09,0x06};
    static const uint8_t R[5] = {0x7F,0x09,0x19,0x29,0x46};
    static const uint8_t S[5] = {0x46,0x49,0x49,0x49,0x31};
    static const uint8_t T[5] = {0x01,0x01,0x7F,0x01,0x01};

    switch (c)
    {
        case 'A': return A;
        case 'C': return C;
        case 'D': return D;
        case 'V': return V;
        case 'm': return m;
        case ':': return colon;
        case '0': return n0;
        case '1': return n1;
        case '2': return n2;
        case '3': return n3;
        case '4': return n4;
        case '5': return n5;
        case '6': return n6;
        case '7': return n7;
        case '8': return n8;
        case '9': return n9;
        case 'E': return E;
        case 'M': return M;
        case 'O': return O;
        case 'P': return P;
        case 'R': return R;
        case 'S': return S;
        case 'T': return T;
        default: return space;
    }
}

static void SSD1306_WriteChar(char c)
{
    const uint8_t *bitmap = get_char_bitmap(c);

    for (uint8_t col = 0; col < 5; col++)
    {
        for (uint8_t row = 0; row < 7; row++)
        {
            if (bitmap[col] & (1 << row))
                SSD1306_DrawPixel(cursor_x + col, cursor_y + row, 1);
        }
    }

    cursor_x += 6;
}

void SSD1306_WriteString(char *str)
{
    while (*str)
    {
        SSD1306_WriteChar(*str++);
    }
}
