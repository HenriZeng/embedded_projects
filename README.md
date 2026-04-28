# Embedded Projects

STM32 embedded learning projects based on STM32 Nucleo-F103RB.

## Development Environment

- Board: STM32 Nucleo-F103RB
- MCU: STM32F103RBT6
- OS: macOS
- IDE: STM32CubeIDE
- Configuration Tool: STM32CubeMX

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
- Supported commands:
  - `ON`
  - `OFF`
  - `TOG`
  - `STATUS`
  - `HELP`
- Case-insensitive command parsing
- CR/LF-based command termination