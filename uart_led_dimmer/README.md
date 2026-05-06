# STM32 UART LED Dimmer


**Version: V1.0**

## 1. Project Title
STM32 UART LED Dimmer

## 2. Project Overview
This project implements a simple UART-controlled PWM dimmer on the STM32 Nucleo-F103RB. It receives text commands over `USART2`, parses them in firmware, and updates the duty cycle on `TIM3 CH1` to control LED brightness through pin `PA6`.

## 3. Hardware Information
- Development board: STM32 Nucleo-F103RB
- MCU: STM32F103RBT6
- Development environment: macOS, STM32CubeIDE, STM32CubeMX
- UART peripheral: `USART2`
- UART TX pin: `PA2`
- UART RX pin: `PA3`
- PWM timer: `TIM3`
- PWM channel: `CH1`
- PWM output pin: `PA6`
- Typical host connection: ST-LINK Virtual COM Port
- Debug/download interface: ST-LINK onboard programmer/debugger

## 4. Features
- Initializes `USART2` for bidirectional serial communication
- Generates PWM output on `TIM3 CH1`
- Controls LED brightness with `SET <0-100>`
- Parses terminal input character by character
- Accepts both `CR` and `LF` as command terminators
- Returns UART feedback such as `PWM=50`

## 5. Supported Commands
- `SET 0`: set PWM duty cycle to 0%
- `SET 50`: set PWM duty cycle to 50%
- `SET 100`: set PWM duty cycle to 100%

Values outside the `0` to `100` range return `Invalid`. The command format is case-sensitive and should be entered as uppercase `SET`.

## 6. How to Use
1. Open the project in STM32CubeIDE.
2. Build and flash the firmware to the Nucleo-F103RB.
3. Open a serial terminal on the ST-LINK Virtual COM Port.
4. Set the terminal to the serial parameters listed below.
5. Reset or run the board.
6. Wait for the startup message `UART LED DIMMER READY>`.
7. Send commands such as `SET 25`, `SET 50`, or `SET 100`.
8. Observe the PWM output on `PA6` and confirm the returned UART feedback.

Example session:

```text
UART LED DIMMER READY>
> SET 25
PWM=25
READY>
> SET 50
PWM=50
READY>
> SET 100
PWM=100
READY>
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
- Character-by-character command parsing
- `CR`/`LF` terminated input handling
- PWM generation using `TIM3 CH1`
- Duty cycle update through timer compare register control

## 9. Project Highlights
- Practical UART-to-PWM control example
- Clear integration of command parsing and timer-based output control
- Useful reference for dimming, motor speed control, or other percentage-based actuators

## 10. Possible Extensions
- Add `GET` or `STATUS` commands for runtime readback
- Add bounds checking messages with more detailed feedback
- Support non-blocking UART reception with interrupts or DMA
- Extend the command set to multiple PWM channels
