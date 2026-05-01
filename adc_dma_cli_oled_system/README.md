# STM32 ADC DMA CLI OLED System

**Version: v1.1**

## 1. Project Title
STM32 ADC DMA CLI OLED System

## 2. Project Overview
This project implements a complete embedded system that integrates ADC sampling, DMA-based UART command interface, and OLED real-time display on the STM32 Nucleo-F103RB. It demonstrates a modular architecture with separation of concerns: CLI for control, ADC for data acquisition, and OLED for visual output. The main loop acts as a simple state machine driven by UART commands.

## 3. Hardware Information
- Development board: STM32 Nucleo-F103RB
- MCU: STM32F103RBT6
- Development environment: macOS, STM32CubeIDE, STM32CubeMX
- ADC peripheral: `ADC1`
- ADC input channel: `ADC_CHANNEL_0`
- Analog input pin: `PA0`
- UART peripheral: `USART2`
- UART TX pin: `PA2`
- UART RX pin: `PA3`
- UART RX DMA channel: `DMA1_Channel6`
- DMA mode: `Circular`
- Baud rate: `115200`
- Display: SSD1306 OLED (128x64, I2C)
- I2C peripheral: `I2C1`
- I2C SCL pin: `PB8` (Arduino D15)
- I2C SDA pin: `PB9` (Arduino D14)
- Supply voltage: `3.3V`
- Typical host connection: ST-LINK Virtual COM Port
- Debug/download interface: ST-LINK onboard programmer/debugger

## 4. Features
- DMA-based UART command input for non-blocking operation
- CLI command parser with modular design
- ADC real-time data acquisition
- OLED display output with continuous refresh capability
- System state control via commands
- Stream-based byte processing without per-byte interrupts
- State-driven behavior with streaming and one-shot modes

## 5. Supported Commands
- `READ`: perform a single ADC sampling and update OLED once
- `STREAM`: start continuous sampling and display updates
- `STOP`: stop continuous updates
- `HELP`: display the supported command list

Commands are case-insensitive because input is normalized to uppercase before command matching.

## 6. How to Use
1. Open the project in STM32CubeIDE.
2. Build and flash the firmware to the Nucleo-F103RB.
3. Connect the SSD1306 OLED display to I2C pins `PB8` (SCL) and `PB9` (SDA).
4. Connect an analog signal source to `PA0` within the valid ADC input range (0-3.3V).
5. Open a serial terminal on the ST-LINK Virtual COM Port.
6. Set the terminal to the serial parameters listed below.
7. Reset or run the board.
8. Wait for the startup banner and prompt.
9. Enter commands such as `READ`, `STREAM`, `STOP`, or `HELP`.

Example session:

```text
ADC DMA CLI OLED System Ready
Type HELP for commands
> READ
ADC=1860  V=1498mV
> STREAM
STREAM ON
> (continuous ADC values displayed on OLED)
STOP
STREAM OFF
> HELP

Commands:
READ    - Read ADC once and update OLED
STREAM  - Start continuous ADC and OLED updates
STOP    - Stop continuous updates
HELP    - Show this message
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
- DMA-based UART RX using `HAL_UART_Receive_DMA()` in circular mode
- Circular receive buffer with continuous hardware-managed data capture
- Main-loop extraction of newly received bytes using `__HAL_DMA_GET_COUNTER()`
- Stream-based byte processing through `CLI_InputChar()` with newline-delimited command parsing
- Modular separation between DMA transport, CLI parsing, ADC acquisition, and OLED rendering
- State-driven behavior using `streaming` and `read_once` flags
- ADC single-channel sampling with 12-bit resolution and voltage conversion
- I2C communication with SSD1306 OLED controller
- Frame buffer-based display rendering
- Non-blocking architecture without per-byte interrupt processing

## 9. Project Highlights
- Clear example of multi-subsystem integration with clean separation of concerns
- Practical reference for command-driven sensor monitoring with visual feedback
- Demonstrates DMA-based UART, ADC acquisition, and I2C display control in a single system
- Higher-throughput architecture than byte-wise interrupt-driven designs
- Lower CPU overhead due to DMA-managed data transfer
- Suitable foundation for data acquisition systems, sensor dashboards, or diagnostic tools

## 10. Changelog

### v1.1
- Added mode display on OLED showing current state (STREAM / STOP)
- Improved READ command behavior for single-shot acquisition
- Added READ highlight indicator when triggered during STREAM mode
- Enhanced state management for clearer system behavior
- Better visual feedback for user interactions

## 11. Possible Extensions
- Add multi-channel ADC support with channel selection commands
- Implement graphical waveform plotting on OLED
- Add data logging to external storage or UART output
- Introduce threshold alarms with visual and UART notifications
- Support configurable sampling rates or averaging modes
- Add calibration or offset adjustment commands
- Extend CLI with system diagnostics or configuration commands
- Move UART transmit to DMA mode for fully asynchronous serial I/O
