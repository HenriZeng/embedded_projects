# STM32 UART DMA CLI

## 1. Project Title
STM32 UART DMA CLI

## 2. Project Overview
This project demonstrates a DMA-based UART command-line interface on the STM32 Nucleo-F103RB. It receives serial data through `USART2` RX in circular DMA mode, tracks newly arrived bytes in the main loop through the DMA counter, feeds them into `CLI_InputChar()`, and controls the onboard LED on `PA5`.

## 3. Hardware Information
- Development board: STM32 Nucleo-F103RB
- MCU: STM32F103RBT6
- Development environment: macOS, STM32CubeIDE, STM32CubeMX
- LED pin: `PA5`
- UART peripheral: `USART2`
- UART TX pin: `PA2`
- UART RX pin: `PA3`
- UART RX DMA channel: `DMA1_Channel6`
- DMA mode: `Circular`
- Baud rate: `115200`
- Typical host connection: ST-LINK Virtual COM Port
- Debug/download interface: ST-LINK onboard programmer/debugger

## 4. Features
- Initializes `USART2` for bidirectional serial communication
- Uses `HAL_UART_Receive_DMA()` for continuous non-blocking UART RX
- Implements a circular DMA receive buffer for continuous input capture
- Detects new data in the main loop using the DMA remaining-count register
- Feeds received bytes into a modular CLI layer with `cli.c` and `cli.h`
- Supports `ON`, `OFF`, `STATUS`, and `HELP`
- Accepts both `CR` and `LF` as command terminators
- Handles case-insensitive input and basic backspace editing
- Processes incoming data as a stream without assuming packet boundaries

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
UART DMA CLI Ready
Type HELP for commands
> ON
LED ON
> OFF
LED OFF
> HELP

Commands:
ON      - Turn LED on
OFF     - Turn LED off
STATUS  - Show LED state
HELP    - Show this message
> STATUS
LED=OFF
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
- DMA-based UART RX using `HAL_UART_Receive_DMA()`
- Circular receive buffer with continuous hardware-managed data capture
- Main-loop extraction of newly received bytes using `__HAL_DMA_GET_COUNTER()`
- Wraparound handling when the DMA write position rolls over the buffer end
- Stream-based byte processing through `CLI_InputChar()` with newline-delimited command parsing
- Modular separation between DMA transport handling and CLI command processing
- No per-byte UART RX interrupt path for command input

## 9. Project Highlights
- Higher-throughput UART CLI architecture than byte-wise interrupt-driven command input
- Lower CPU overhead than per-byte interrupt handling because DMA moves RX data into memory autonomously
- More robust under continuous input than simple polling designs that wait on each received byte
- Good reference for combining circular DMA buffering with reusable CLI parsing on STM32
- Suitable foundation for more demanding diagnostics, service ports, or serial control interfaces

## 10. Possible Extensions
- Add idle-line detection to reduce command-processing latency
- Move UART transmit to DMA mode for fully asynchronous serial I/O
- Add overflow detection and reporting for heavy serial traffic
- Extend the CLI with version, uptime, GPIO, or diagnostic commands
- Generalize the DMA receive path for multiple UART channels
