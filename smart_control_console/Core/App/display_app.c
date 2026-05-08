/**
  ******************************************************************************
  * @file           : display_app.c
  * @brief          : Display Application Layer Implementation
  * @author         : Smart Control Console Team
  * @version        : V0.2
  ******************************************************************************
  * @attention
  *
  * This module provides high-level display functions for OLED screen
  * with formatted data presentation.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "display_app.h"
#include "ssd1306.h"
#include <stdio.h>
#include <string.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define LINE_HEIGHT         16      // Pixels between lines

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static char line_buffer[32];

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/**
  * @brief  Initialize display application module
  * @retval None
  */
void Display_App_Init(void)
{
    SSD1306_Init();
    SSD1306_Clear();
    
    // Show splash screen
    SSD1306_SetCursor(0, 0);
    SSD1306_WriteString("SMART CONSOLE");
    SSD1306_SetCursor(0, 16);
    SSD1306_WriteString("V0.2");
    SSD1306_SetCursor(0, 32);
    SSD1306_WriteString("INITIALIZING...");
    SSD1306_UpdateScreen();
    
    HAL_Delay(1000);
}

/**
  * @brief  Update display with sensor and control data
  * @param  adc: Raw ADC value (0-4095)
  * @param  mv: Voltage in millivolts
  * @param  pwm_percent: PWM duty cycle percentage (0-100)
  * @retval None
  */
void Display_App_Update(uint32_t adc, uint32_t mv, uint32_t pwm_percent)
{
    SSD1306_Clear();
    
    // Line 1: ADC value
    snprintf(line_buffer, sizeof(line_buffer), "ADC:%lu", adc);
    SSD1306_SetCursor(0, 0);
    SSD1306_WriteString(line_buffer);
    
    // Line 2: Voltage
    snprintf(line_buffer, sizeof(line_buffer), "V:%lumV", mv);
    SSD1306_SetCursor(0, LINE_HEIGHT);
    SSD1306_WriteString(line_buffer);
    
    // Line 3: PWM percentage
    snprintf(line_buffer, sizeof(line_buffer), "PWM:%lu%%", pwm_percent);
    SSD1306_SetCursor(0, LINE_HEIGHT * 2);
    SSD1306_WriteString(line_buffer);
    
    // Line 4: Mode indicator
    SSD1306_SetCursor(0, LINE_HEIGHT * 3);
    SSD1306_WriteString("MODE:MONITOR");
    
    SSD1306_UpdateScreen();
}

/**
  * @brief  Display error message
  * @param  error_msg: Error message string (max 20 chars)
  * @retval None
  */
void Display_App_ShowError(const char *error_msg)
{
    SSD1306_Clear();
    
    SSD1306_SetCursor(0, 0);
    SSD1306_WriteString("ERROR:");
    
    SSD1306_SetCursor(0, LINE_HEIGHT);
    SSD1306_WriteString((char *)error_msg);
    
    SSD1306_UpdateScreen();
}

/**
  * @brief  Display custom message
  * @param  line1: First line text
  * @param  line2: Second line text
  * @param  line3: Third line text
  * @param  line4: Fourth line text
  * @retval None
  */
void Display_App_ShowMessage(const char *line1, const char *line2, 
                              const char *line3, const char *line4)
{
    SSD1306_Clear();
    
    if (line1 != NULL)
    {
        SSD1306_SetCursor(0, 0);
        SSD1306_WriteString((char *)line1);
    }
    
    if (line2 != NULL)
    {
        SSD1306_SetCursor(0, LINE_HEIGHT);
        SSD1306_WriteString((char *)line2);
    }
    
    if (line3 != NULL)
    {
        SSD1306_SetCursor(0, LINE_HEIGHT * 2);
        SSD1306_WriteString((char *)line3);
    }
    
    if (line4 != NULL)
    {
        SSD1306_SetCursor(0, LINE_HEIGHT * 3);
        SSD1306_WriteString((char *)line4);
    }
    
    SSD1306_UpdateScreen();
}

/**
  * @brief  Clear display screen
  * @retval None
  */
void Display_App_Clear(void)
{
    SSD1306_Clear();
    SSD1306_UpdateScreen();
}
