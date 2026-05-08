/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : SG90 Servo Control System
  * @version        : V1.0
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SERVO_CONTROL_PERIOD_MS 2U
#define SERVO_SCAN_DEBOUNCE_MS  250U
#define ADC_FILTER_SHIFT        3U
#define SERVO_ADC_DEADBAND      12U
#define SERVO_PULSE_DEADBAND_US 8U

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */
static uint8_t Is_User_Button_Pressed(void);
static void Run_Servo_ManualScanMode(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
  * @brief  Read ADC value from potentiometer
  * @retval ADC value (0-4095)
  */
uint32_t Read_ADC_Value(void)
{
    uint32_t adc_value = 0;
    
    // Start ADC conversion
    HAL_ADC_Start(&hadc1);
    
    // Wait for conversion to complete
    if (HAL_ADC_PollForConversion(&hadc1, 5) == HAL_OK)
    {
        // Read ADC value
        adc_value = HAL_ADC_GetValue(&hadc1);
    }
    
    // Stop ADC
    HAL_ADC_Stop(&hadc1);
    
    return adc_value;
}

static uint32_t Apply_ADC_Filter(uint32_t raw_adc, uint32_t *state)
{
    if (*state == 0U)
    {
        *state = raw_adc << ADC_FILTER_SHIFT;
    }
    else
    {
        *state = *state - (*state >> ADC_FILTER_SHIFT) + raw_adc;
    }

    return (*state >> ADC_FILTER_SHIFT);
}

/**
  * @brief  Convert ADC value to servo angle
  * @param  adc: ADC value (0-4095)
  * @retval Angle in degrees (0-180)
  */
uint32_t ADC_To_Angle(uint32_t adc)
{
    // Map ADC range (0-4095) to angle range (0-180)
    // angle = (adc * 180) / 4095
    uint32_t angle = (adc * 180) / 4095;
    
    // Ensure angle is within valid range
    if (angle > 180)
    {
        angle = 180;
    }
    
    return angle;
}

/**
  * @brief  Convert servo angle to PWM pulse width
  * @param  angle: Servo angle in degrees (0-180)
  * @retval PWM pulse value for TIM3 CCR
  * 
  * @note   SG90 Servo timing:
  *         - 0°   = 500us pulse
  *         - 90°  = 1500us pulse
  *         - 180° = 2500us pulse
  *         
  *         TIM3 Configuration:
  *         - Prescaler = 7 (8MHz / 8 = 1MHz timer clock)
  *         - Period = 19999 (20ms PWM period for 50Hz)
  *         - 1 tick = 1us
  *         
  *         Therefore:
  *         - pulse_us = 500 + (angle * 2000 / 180)
  *         - CCR value = pulse_us (since 1 tick = 1us)
  */
uint32_t Servo_Angle_To_Pulse(uint32_t angle)
{
    // Ensure angle is within valid range
    if (angle > 180)
    {
        angle = 180;
    }
    
    // Calculate pulse width in microseconds
    // 0° → 500us, 180° → 2500us
    // pulse = 500 + (angle * 2000 / 180)
    uint32_t pulse_us = 500 + (angle * 2000) / 180;
    
    // Return CCR value (1 tick = 1us)
    return pulse_us;
}

static uint8_t Is_User_Button_Pressed(void)
{
    return (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_RESET) ? 1U : 0U;
}

static void Run_Servo_ManualScanMode(void)
{
    static const uint32_t scan_pulses[] = {700, 800, 900, 1100, 1300, 1500, 1700, 1900, 2100, 2200, 2300};
    uint32_t index = 0;
    uint32_t pulse = scan_pulses[index];

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse);

    while (Is_User_Button_Pressed() != 0U)
    {
        HAL_Delay(10);
    }

    while (1)
    {
        if (Is_User_Button_Pressed() != 0U)
        {
            HAL_Delay(20);
            if (Is_User_Button_Pressed() != 0U)
            {
                index++;
                if (index >= (sizeof(scan_pulses) / sizeof(scan_pulses[0])))
                {
                    index = 0;
                }

                pulse = scan_pulses[index];
                __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse);

                while (Is_User_Button_Pressed() != 0U)
                {
                    HAL_Delay(10);
                }

                HAL_Delay(SERVO_SCAN_DEBOUNCE_MS);
            }
        }
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  /* Application initialization */

  /* Start PWM and move the servo to center position. */
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  uint32_t center_pulse = Servo_Angle_To_Pulse(90);
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, center_pulse);

  if (Is_User_Button_Pressed() != 0U)
  {
    Run_Servo_ManualScanMode();
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint32_t adc_value = 0;
  uint32_t raw_adc_value = 0;
  uint32_t angle = 90;
  uint32_t pulse = center_pulse;
  uint32_t filtered_adc_accum = 0;
  uint32_t servo_adc_value = 0;
  uint32_t last_servo_adc_value = 0;
  uint32_t last_servo_pulse = center_pulse;
  uint32_t last_control_tick = HAL_GetTick();

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    uint32_t now = HAL_GetTick();

    if ((now - last_control_tick) >= SERVO_CONTROL_PERIOD_MS)
    {
      last_control_tick = now;

      // Step 1: Read ADC value from potentiometer
      raw_adc_value = Read_ADC_Value();
      adc_value = Apply_ADC_Filter(raw_adc_value, &filtered_adc_accum);

      // Step 2: Ignore small ADC jitter before updating servo target.
      servo_adc_value = adc_value;
      if (last_servo_adc_value == 0U)
      {
        last_servo_adc_value = servo_adc_value;
      }

      if (((servo_adc_value > last_servo_adc_value) ? (servo_adc_value - last_servo_adc_value)
                                                    : (last_servo_adc_value - servo_adc_value)) >= SERVO_ADC_DEADBAND)
      {
        last_servo_adc_value = servo_adc_value;
      }

      angle = ADC_To_Angle(last_servo_adc_value);

      // Step 3: Convert angle to PWM pulse width
      pulse = Servo_Angle_To_Pulse(angle);

      // Step 4: Ignore tiny pulse changes so the servo does not hunt in place.
      if (((pulse > last_servo_pulse) ? (pulse - last_servo_pulse)
                                      : (last_servo_pulse - pulse)) >= SERVO_PULSE_DEADBAND_US)
      {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse);
        last_servo_pulse = pulse;
      }
    }
  /* USER CODE END 3 */
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 7;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 19999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
