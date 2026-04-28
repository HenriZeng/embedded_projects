# STM32 LED Blink Demo

## 1. Project Title
STM32 LED Blink Demo

## 2. Project Overview
This project is a minimal STM32F103 bring-up example that blinks the onboard user LED on the Nucleo-F103RB. It is intended as a clean starting point for validating the toolchain, board wiring, clock setup, and GPIO output control.

## 3. Hardware Information
- Development board: STM32 Nucleo-F103RB
- MCU: STM32F103RBT6
- Development environment: macOS, STM32CubeIDE, STM32CubeMX
- LED pin: `PA5` (commonly mapped to the onboard user LED on Nucleo boards)
- Serial interface: Not used in this project
- Debug/download interface: ST-LINK onboard programmer/debugger

## 4. Features
- Initializes the STM32F103 basic runtime with HAL
- Configures `PA5` as a push-pull GPIO output
- Toggles the LED continuously
- Uses a fixed 500 ms delay to create a visible blink pattern

## 5. Supported Commands
This project does not implement UART or command-line interaction.

## 6. How to Use
1. Open the project in STM32CubeIDE.
2. Build the firmware.
3. Flash the binary to the STM32 Nucleo-F103RB through ST-LINK.
4. Reset or run the board.
5. Verify that the LED on `PA5` blinks at a steady rate.

For a quick functional test, confirm that the LED changes state every 500 ms.

## 7. Serial Configuration
Not applicable.

## 8. Key Technical Points
- GPIO output configuration with STM32 HAL
- Basic main loop control
- SysTick-based timing via `HAL_Delay()`
- Simple board-level hardware verification

## 9. Project Highlights
- Minimal and easy to understand
- Good first-step validation project for a new STM32 setup
- Clean baseline for extending into timer, interrupt, or RTOS-based designs

## 10. Possible Extensions
- Replace `HAL_Delay()` with a timer interrupt for non-blocking blinking
- Add button input to control blink speed or mode
- Add UART logging for runtime status messages
- Expand into a heartbeat/status indicator module for larger projects
