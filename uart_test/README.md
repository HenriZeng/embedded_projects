# STM32 UART Transmission Test


**Version: V1.0**

## 1. Project Title
STM32 UART Transmission Test

## 2. Project Overview
This project demonstrates basic UART communication on the STM32 Nucleo-F103RB. It periodically transmits a test string over `USART2` while toggling the onboard LED, making it useful for verifying both serial output and GPIO behavior during early firmware bring-up.

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
- Initializes `USART2` for asynchronous serial communication
- Sends `Hello STM32 UART` once per second
- Toggles the LED on `PA5` in sync with transmission
- Provides a simple end-to-end hardware validation example

## 5. Supported Commands
This project does not parse incoming serial commands. It only transmits periodic status text.

## 6. How to Use
1. Open the project in STM32CubeIDE.
2. Build and flash the firmware to the Nucleo-F103RB.
3. Open a serial terminal on the ST-LINK Virtual COM Port.
4. Reset or run the board.
5. Observe the message `Hello STM32 UART` every second and confirm the LED is toggling.

Suggested terminal tools include `screen`, `minicom`, CoolTerm, or any USB serial monitor.

## 7. Serial Configuration
- Baud rate: `115200`
- Data bits: `8`
- Parity: `None`
- Stop bits: `1`
- Flow control: `None`
- Line ending for manual tests: `CRLF` or `LF` is acceptable, although the firmware only transmits data

## 8. Key Technical Points
- UART initialization with STM32 HAL
- Blocking transmission using `HAL_UART_Transmit()`
- GPIO output control for visual runtime feedback
- Basic cyclic task structure inside the main loop

## 9. Project Highlights
- Straightforward UART validation project
- Combines serial output and LED indication for easy debugging
- Good reference for early communication-layer testing

## 10. Possible Extensions
- Add UART receive support and echo functionality
- Move transmission to interrupts or DMA
- Add command parsing for runtime control
- Introduce structured logging or a lightweight debug console
