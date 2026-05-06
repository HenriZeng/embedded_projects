# STM32 ADC UART Monitor


**Version: V1.0**

## 1. Project Title
STM32 ADC UART Monitor

## 2. Project Overview
This project demonstrates a simple ADC monitoring workflow on the STM32 Nucleo-F103RB. It samples an analog input with `ADC1` on `PA0`, receives single-character control commands over `USART2`, and sends ADC readings back to the host through the serial port.

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
- Additional GPIO configured: `PA5` output
- Typical host connection: ST-LINK Virtual COM Port
- Debug/download interface: ST-LINK onboard programmer/debugger

## 4. Features
- Initializes `ADC1` for continuous conversion
- Starts ADC conversion during system initialization
- Receives single-character UART control commands
- Returns one ADC sample when the host sends `r`
- Enters periodic streaming mode when the host sends `s`
- Stops streaming mode when the host sends `x`
- Reports sampled values in plain text such as `ADC=1234`

## 5. Supported Commands
- `r`: read one ADC value immediately
- `s`: start continuous streaming output
- `x`: stop continuous streaming output

Commands are lowercase in the current firmware implementation.

## 6. How to Use
1. Open the project in STM32CubeIDE.
2. Build and flash the firmware to the Nucleo-F103RB.
3. Connect an analog signal source to `PA0` within the valid ADC input range.
4. Open a serial terminal on the ST-LINK Virtual COM Port.
5. Set the terminal to the serial parameters listed below.
6. Reset or run the board.
7. Send `r` to read a single sample.
8. Send `s` to start periodic sampling output every 500 ms.
9. Send `x` to stop the stream.

Example session:

```text
r
ADC=1860
s
ADC=1858
ADC=1861
ADC=1859
x
```

## 7. Serial Configuration
- Baud rate: `115200`
- Data bits: `8`
- Parity: `None`
- Stop bits: `1`
- Flow control: `None`
- Recommended terminal input: send plain characters `r`, `s`, and `x`

The firmware reads UART data one byte at a time, so line ending configuration is not critical for basic testing.

## 8. Key Technical Points
- ADC initialization with STM32 HAL
- Continuous conversion on `ADC1`
- Polling-based conversion readout with `HAL_ADC_PollForConversion()`
- UART receive/transmit with STM32 HAL
- Simple single-byte command handling
- Periodic stream output controlled by a firmware state flag

## 9. Project Highlights
- Straightforward ADC-to-UART monitoring example
- Useful for validating analog input acquisition and serial reporting together
- Good reference for sensor bring-up, voltage observation, or quick bench testing

## 10. Possible Extensions
- Add command acknowledgements and a startup banner
- Support uppercase commands and line-based parsing
- Convert raw ADC values to voltage for easier interpretation
- Move UART receive and ADC sampling to interrupts or DMA
- Add multi-channel sampling and timestamped output
