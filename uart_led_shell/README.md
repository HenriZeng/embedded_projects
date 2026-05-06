# STM32 UART LED Command Shell


**Version: V1.0**

## 1. Project Title
STM32 UART LED Command Shell

## 2. Project Overview
This project implements a simple serial command shell on the STM32 Nucleo-F103RB for controlling the onboard LED. It receives text commands over `USART2`, parses them in firmware, updates LED state on `PA5`, and returns command responses through the serial terminal.

## 3. Hardware Information
- Development board: STM32 Nucleo-F103RB
- MCU: STM32F103RBT6
- Development environment: macOS, STM32CubeIDE, STM32CubeMX
- LED pin: `PA5`
- UART peripheral: `USART2`
- UART TX pin: `PA2`
- UART RX pin: `PA3`
- Typical host connection: ST-LINK Virtual COM Port
- Debug/download interface: ST-LINK onboard programmer/debugger

## 4. Features
- Initializes `USART2` for bidirectional serial communication
- Accepts text commands from a terminal
- Controls the LED with `ON`, `OFF`, and `TOG`
- Reports current LED state with `STATUS`
- Displays a simple help message with `HELP`
- Prints a prompt after each command

## 5. Supported Commands
- `ON`: turn the LED on
- `OFF`: turn the LED off
- `TOG`: toggle the LED state
- `STATUS`: print the current LED status
- `HELP`: display the supported command list

Commands are case-insensitive because input is converted to uppercase before comparison.

## 6. How to Use
1. Open the project in STM32CubeIDE.
2. Build and flash the firmware to the Nucleo-F103RB.
3. Open a serial terminal on the ST-LINK Virtual COM Port.
4. Set the terminal to the serial parameters listed below.
5. Reset or run the board.
6. Wait for the startup banner and prompt.
7. Enter commands such as `ON`, `OFF`, `TOG`, `STATUS`, or `HELP`.

Example session:

```text
UART CMD READY
Commands: ON / OFF / TOG
> help
Commands:
ON     - turn LED on
OFF    - turn LED off
TOG    - toggle LED
STATUS - show LED state
> status
LED STATE: OFF
```

## 7. Serial Configuration
- Baud rate: `115200`
- Data bits: `8`
- Parity: `None`
- Stop bits: `1`
- Flow control: `None`
- Recommended line ending: `CRLF`

The firmware treats both carriage return (`\r`) and line feed (`\n`) as command terminators.

## 8. Key Technical Points
- UART receive/transmit with STM32 HAL
- Character-by-character command buffering
- Fixed-length input buffer management
- Case normalization with `toupper()`
- Command parsing with string comparison
- GPIO-based LED control with internal state tracking

## 9. Project Highlights
- Clear example of a lightweight embedded command-line interface
- Practical combination of UART, GPIO, and command parsing
- Useful stepping stone toward menu-driven diagnostics or service firmware
- Easy to demo in interviews, portfolios, or GitHub project pages

## 10. Possible Extensions
- Add backspace handling and input editing
- Implement non-blocking receive with interrupts or DMA
- Introduce a command table for easier feature scaling
- Add PWM-based brightness control and timing commands
- Expand the shell with GPIO readout, version info, or self-test commands
