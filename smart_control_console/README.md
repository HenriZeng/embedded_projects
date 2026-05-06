# STM32 Smart Control Console

**Version: V0.1**

## 1. Project Title
STM32 Smart Control Console

## 2. Project Overview
This project implements a potentiometer-based ADC monitoring system on the STM32 Nucleo-F103RB. It reads analog voltage from a potentiometer through ADC1, converts the data to millivolts, and outputs real-time ADC values and voltage readings via UART2. The system uses software-triggered polling mode for ADC acquisition with printf redirection for convenient serial output.

## 3. Hardware Information
- Development board: STM32 Nucleo-F103RB
- MCU: STM32F103RBT6
- Development environment: macOS, STM32CubeIDE, STM32CubeMX
- ADC peripheral: `ADC1`
- ADC input channel: `ADC_CHANNEL_0`
- Analog input pin: `PA0` (ADC1_IN0)
- Input device: Potentiometer (0-3.3V range)
- UART peripheral: `USART2`
- UART TX pin: `PA2`
- UART RX pin: `PA3`
- Baud rate: `115200`
- Supply voltage: `3.3V`
- Typical host connection: ST-LINK Virtual COM Port
- Debug/download interface: ST-LINK onboard programmer/debugger

## 4. Features
- ADC single-channel sampling on PA0
- Potentiometer analog input reading (0-3.3V)
- Software-triggered ADC conversion
- Polling mode ADC readout
- 12-bit ADC resolution with voltage conversion to millivolts
- UART2 serial output of ADC values and voltage
- Printf redirection for convenient debugging
- Verified voltage range: 0V ~ 3.3V

## 5. System Behavior
- System initializes ADC1 and USART2
- Main loop continuously triggers ADC conversion
- ADC reads potentiometer voltage on PA0
- Raw ADC value and calculated voltage are sent via UART
- Printf output format: `ADC=XXXX  V=XXXXmV`
- Continuous monitoring with periodic updates

## 6. How to Use
1. Open the project in STM32CubeIDE.
2. Build and flash the firmware to the Nucleo-F103RB.
3. Connect a potentiometer to PA0:
   - One end to GND
   - Other end to 3.3V
   - Wiper (middle pin) to PA0
4. Open a serial terminal on the ST-LINK Virtual COM Port.
5. Set the terminal to the serial parameters listed below.
6. Reset or run the board.
7. Adjust the potentiometer and observe real-time ADC values in the terminal.

Example output:

```text
ADC=0     V=0mV
ADC=1024  V=825mV
ADC=2048  V=1650mV
ADC=3072  V=2475mV
ADC=4095  V=3300mV
```

## 7. Serial Configuration
- Baud rate: `115200`
- Data bits: `8`
- Parity: `None`
- Stop bits: `1`
- Flow control: `None`

## 8. Key Technical Points
- ADC single-channel configuration on PA0
- Software-triggered conversion using `HAL_ADC_Start()`
- Polling-based readout with `HAL_ADC_PollForConversion()`
- 12-bit ADC resolution (0-4095)
- Voltage calculation: `voltage_mV = (adc_value * 3300) / 4095`
- Printf redirection through UART for convenient output
- `__io_putchar()` implementation for printf support
- Continuous sampling in main loop

## 9. Project Highlights
- Simple and clear ADC monitoring example
- Practical reference for analog input reading
- Printf redirection demonstrates convenient debugging technique
- Suitable foundation for sensor monitoring, user input, or control systems
- Verified full-range voltage reading (0-3.3V)

## 10. Changelog

### V0.1 (Initial Release)
- ADC1 single-channel sampling on PA0
- Potentiometer analog input support
- UART2 serial output
- Printf redirection implementation
- Software-triggered polling mode
- Voltage range verification (0V ~ 3.3V)
- STM32CubeMX configuration synchronized

## 11. Possible Extensions
- Add multi-channel ADC support for multiple analog inputs
- Implement DMA-based ADC for continuous background sampling
- Add filtering or averaging for stable readings
- Introduce threshold detection with LED indicators
- Add UART command interface for control
- Implement data logging or graphing capabilities
- Support calibration or offset adjustment
- Add interrupt-based ADC conversion for better timing control
