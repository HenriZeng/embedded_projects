# STM32 ADC CLI Monitor

## 1. Project Title
STM32 ADC CLI Monitor

## 2. Project Overview
This project implements an interactive ADC monitoring interface on the STM32 Nucleo-F103RB. It receives line-based commands over `USART2` using interrupt-driven UART input, samples `ADC1` on `PA0` in polling mode, and reports ADC values and calculated voltage through a modular CLI layer.

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
- Baud rate: `115200`
- Additional GPIO configured: `PA5` output
- Typical host connection: ST-LINK Virtual COM Port
- Debug/download interface: ST-LINK onboard programmer/debugger

## 4. Features
- Initializes `USART2` for bidirectional serial communication
- Uses `HAL_UART_Receive_IT()` for non-blocking UART command input
- Implements a modular CLI layer with `cli.c` and `cli.h`
- Uses polling-based ADC sampling through `ADC1`
- Reports both raw ADC value and calculated millivolt reading
- Supports single-shot read and continuous stream control commands
- Uses a state-based `streaming` flag to control periodic output
- Accepts both `CR` and `LF` as command terminators
- Handles case-insensitive input and basic backspace editing

## 5. Supported Commands
- `READ`: read one ADC value immediately
- `STREAM`: start continuous ADC output
- `STOP`: stop continuous ADC output
- `HELP`: display the supported command list

Commands are case-insensitive because input is normalized to uppercase before command matching.

## 6. How to Use
1. Open the project in STM32CubeIDE.
2. Build and flash the firmware to the Nucleo-F103RB.
3. Connect an analog signal source to `PA0` within the valid ADC input range.
4. Open a serial terminal on the ST-LINK Virtual COM Port.
5. Set the terminal to the serial parameters listed below.
6. Reset or run the board.
7. Wait for the startup banner and prompt.
8. Enter commands such as `READ`, `STREAM`, `STOP`, or `HELP`.

Example session:

```text
BOOT OK
ADC CLI Monitor Ready
Type HELP
> read
ADC=1860  V=1498mV
> stream
STREAM ON
> ADC=1858  V=1496mV
ADC=1861  V=1499mV
ADC=1859  V=1498mV
stop
STREAM OFF
> help
Commands:
READ   - Read ADC once
STREAM - Start continuous ADC output
STOP   - Stop continuous ADC output
HELP   - Show this message
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
- Byte-wise command buffering with completion on `CR` or `LF`
- Modular separation between CLI parsing and ADC application logic
- Polling-based ADC readout with `HAL_ADC_PollForConversion()`
- Continuous conversion enabled on `ADC1`
- State-based streaming control through a shared runtime flag
- UART-formatted reporting of raw ADC code and converted voltage

## 9. Project Highlights
- Clear example of combining a reusable CLI module with ADC monitoring
- Practical reference for non-blocking command input with polling-based sampling
- Simple state-machine style design for runtime stream control
- Suitable foundation for sensor diagnostics, bench monitoring, or service tools

## 10. Possible Extensions
- Add configurable stream interval or threshold commands
- Move ADC acquisition to interrupt or DMA mode for higher-rate sampling
- Add filtering, averaging, or min/max statistics commands
- Support multiple ADC channels and channel selection commands
- Introduce calibration or reference-voltage reporting features
