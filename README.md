# Embedded Projects

STM32 embedded learning projects based on STM32 Nucleo-F103RB.

## Development Environment

- Board: STM32 Nucleo-F103RB
- MCU: STM32F103RBT6
- OS: macOS
- IDE: STM32CubeIDE
- Configuration Tool: STM32CubeMX

## New Project Workflow

New STM32 projects in this workspace are created from an external template repository instead of copying an existing project manually.

- Template repository: `/Users/henri/git/stm32-template-f103rb-base`
- Project creation script: `/Users/henri/STM32CubeIDE/workspace_2.1.1/new_stm32_project.sh`

### Create a New Project

```bash
./new_stm32_project.sh motor_driver
```

The script will:

- Copy the template repository into this workspace
- Create a new project folder using the target project name
- Remove copied Git-related files such as `.git` and `.gitignore`
- Rename `stm32_template.ioc` to the new project name
- Update project name references in `README.md` and `RENAME_PROJECT.md`

### After Running the Script

You still need to:

1. Open the new `.ioc` file in STM32CubeIDE or STM32CubeMX
2. Confirm the `Project Name` matches the new project name
3. Regenerate STM32CubeIDE project files
4. Build and verify the project

## Projects

### 1. led_blink

Basic GPIO output demo.

Features:
- Configure PA5 as GPIO output
- Toggle LD2 LED periodically

### 2. uart_test

Basic UART transmission demo.

Features:
- Configure USART2 at 115200 baud rate
- Send text from STM32 to Mac serial terminal
- Verify UART TX communication

### 3. uart_led_shell

UART-based LED command shell.

Features:
- Receive commands from serial terminal
- Control LD2 LED with commands
- Supported commands: `ON`, `OFF`, `TOG`, `STATUS`, `HELP`
- Case-insensitive command parsing
- CR/LF-based command termination

### 4. uart_cli_interrupt

Interrupt-driven UART command-line interface.

Features:
- Interrupt-based UART RX using `HAL_UART_Receive_IT()`
- Modular CLI layer with command parsing
- LED control via serial commands
- Non-blocking command input

### 5. uart_dma_cli

DMA-based UART command-line interface.

Features:
- DMA circular mode for UART RX
- Higher throughput than interrupt-driven approach
- Stream-based byte processing
- Lower CPU overhead
- LED control via serial commands

### 6. uart_led_dimmer

UART-controlled PWM LED dimmer.

Features:
- PWM generation using TIM3 CH1
- UART command interface for brightness control
- `SET <0-100>` command for duty cycle adjustment
- Real-time PWM output on PA6

### 7. adc_uart_monitor

ADC monitoring with UART output.

Features:
- ADC single-channel sampling on PA0
- Voltage conversion (12-bit ADC → mV)
- UART output of ADC values
- Polling-based ADC readout

### 8. adc_cli_monitor

Interactive ADC monitoring with CLI.

Features:
- Interrupt-driven UART CLI
- ADC sampling on PA0
- Commands: `READ`, `STREAM`, `STOP`, `HELP`
- Real-time voltage reporting via UART
- State-based streaming control

### 9. interactive_buzzer

Button-controlled PWM buzzer.

Features:
- Button input on PC13 (USER button)
- PWM output on PA6 (TIM3 CH1)
- LED status indication on PA5
- Real-time input-driven output control

### 10. adc_oled_monitor

Real-time ADC display on OLED.

Features:
- ADC sampling on PA0
- SSD1306 OLED display (128x64, I2C)
- Real-time ADC value and voltage display
- I2C communication on PB8/PB9

### 11. adc_dma_cli_oled_system

**Version: v1.1**

Integrated system with DMA CLI, ADC, and OLED display.

Features:
- DMA-based UART command interface
- ADC real-time data acquisition
- OLED display output with mode indication
- Commands: `READ`, `STREAM`, `STOP`, `HELP`
- State-driven behavior with visual feedback
- Modular architecture with separation of concerns

Recent improvements (v1.1):
- Mode display on OLED (STREAM / STOP)
- READ highlight indicator in STREAM mode
- Enhanced state management
- Improved single-shot READ behavior

## Project Categories

### Basic I/O
- `led_blink` - GPIO output
- `interactive_buzzer` - Button + PWM + LED

### UART Communication
- `uart_test` - Basic UART TX
- `uart_led_shell` - Simple command shell
- `uart_cli_interrupt` - Interrupt-driven CLI
- `uart_dma_cli` - DMA-based CLI
- `uart_led_dimmer` - PWM control via UART

### ADC & Sensors
- `adc_uart_monitor` - ADC with UART output
- `adc_cli_monitor` - ADC with CLI control
- `adc_oled_monitor` - ADC with OLED display

### Integrated Systems
- `adc_dma_cli_oled_system` - Complete data acquisition system with CLI and display

## Common Hardware Configuration

- UART: USART2 (PA2/TX, PA3/RX) @ 115200 baud
- LED: PA5 (LD2)
- Button: PC13 (USER button)
- ADC: PA0 (ADC1_IN0)
- PWM: PA6 (TIM3 CH1)
- I2C: PB8 (SCL), PB9 (SDA) - Arduino D15/D14
