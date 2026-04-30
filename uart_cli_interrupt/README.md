# STM32 UART CLI Interrupt

## 1. Project Title
STM32 UART CLI Interrupt

## 2. Project Overview
This project implements a simple interrupt-driven UART command-line interface on the STM32 Nucleo-F103RB. It receives characters over `USART2` without blocking the main loop, assembles line-based commands in firmware, dispatches them through a command table, and controls the onboard LED on `PA5`.

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
- Uses `HAL_UART_Receive_IT()` for interrupt-driven UART reception
- Implements a modular CLI layer with `cli.c` and `cli.h`
- Dispatches commands through a function-pointer command table
- Supports `ON`, `OFF`, `STATUS`, and `HELP`
- Accepts both `CR` and `LF` as command terminators
- Handles case-insensitive input and basic backspace editing
- Prints a startup banner and prompt over UART

## 5. Supported Commands
- `ON`: turn the LED on
- `OFF`: turn the LED off
- `STATUS`: print the current LED state
- `HELP`: display the supported command list

Commands are case-insensitive because input is normalized to uppercase before command matching.

## 6. How to Use
1. Open the project in STM32CubeIDE.
2. Build and flash the firmware to the Nucleo-F103RB.
3. Open a serial terminal on the ST-LINK Virtual COM Port.
4. Set the terminal to the serial parameters listed below.
5. Reset or run the board.
6. Wait for the startup banner and prompt.
7. Enter commands such as `ON`, `OFF`, `STATUS`, or `HELP`.

Example session:

```text
UART CLI Ready
> help

Commands:
ON      - Turn LED ON
OFF     - Turn LED OFF
STATUS  - Show LED state
HELP    - Show this message
> status
LED=OFF
> on
LED ON
> status
LED=ON
> test
Unknown CMD
>
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
- Interrupt-driven UART receive path using `HAL_UART_RxCpltCallback()`
- Byte-wise input buffering with command completion on `CR` or `LF`
- Modular CLI implementation separated from `main.c`
- Function-pointer command dispatch through a static command table
- Case normalization for command matching
- Backspace support for simple line editing
- GPIO-based LED control on `PA5`

## 9. Project Highlights
- Clear example of a non-blocking UART CLI on STM32
- Good reference for separating command parsing into a reusable module
- Practical combination of UART interrupts, command parsing, and GPIO control
- Suitable foundation for expanding into diagnostic or service interfaces

## 10. Possible Extensions
- Add command arguments and parameter parsing
- Move UART transmit to interrupt or DMA mode for fully asynchronous I/O
- Add ring-buffered input for higher-throughput command handling
- Introduce more system commands such as version, uptime, or GPIO readback
- Extend the CLI framework to support multiple peripherals or subsystems
