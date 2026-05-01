# STM32 Interactive Buzzer

## 1. Project Title
STM32 Interactive Buzzer

## 2. Project Overview
This project implements a simple interactive input-output system on the STM32 Nucleo-F103RB. It uses a push button to control a PWM-driven buzzer with LED status indication. The system provides real-time button-driven output control with clean separation of input and output logic.

## 3. Hardware Information
- Development board: STM32 Nucleo-F103RB
- MCU: STM32F103RBT6
- Development environment: macOS, STM32CubeIDE, STM32CubeMX
- Button input: `PC13` (built-in USER button)
- PWM timer: `TIM3`
- PWM channel: `CH1`
- PWM output pin: `PA6`
- LED pin: `PA5` (LD2)
- Debug/download interface: ST-LINK onboard programmer/debugger

## 4. Features
- Button-controlled PWM output
- LED status indication
- Simple real-time control loop
- Clean separation of input and output logic

## 5. System Behavior
When the button is pressed:
- LED turns ON
- PWM output is enabled to drive the buzzer

When the button is released:
- LED turns OFF
- PWM output is disabled

## 6. How to Use
1. Open the project in STM32CubeIDE.
2. Build and flash the firmware to the Nucleo-F103RB.
3. Connect a buzzer to `PA6` (see hardware notes below).
4. Reset or run the board.
5. Press the USER button on `PC13`.
6. Observe the LED on `PA5` and listen for buzzer output.

Example interaction:

```text
User presses button   → LED ON  → PWM enabled  → Buzzer sounds
User releases button  → LED OFF → PWM disabled → Buzzer stops
```

## 7. Hardware Notes
- The buzzer used is a passive piezo element
- Direct MCU drive may produce weak or no audible sound
- For reliable sound output, a transistor driver or active buzzer module is recommended

## 8. Key Technical Points
- GPIO input with pull-up configuration on `PC13`
- PWM generation using `TIM3 CH1`
- Duty cycle control using `__HAL_TIM_SET_COMPARE()`
- Real-time input-driven output control
- Modular embedded design approach

## 9. Project Highlights
- Clear example of button-controlled PWM output
- Practical reference for real-time input-output interaction
- Simple state-driven control without complex state machines
- Suitable foundation for interactive embedded systems

## 10. Possible Extensions
- Add multiple PWM frequencies for different tones
- Implement button debouncing for cleaner state transitions
- Add melody playback with timer-based sequencing
- Support multiple buttons for different sound patterns
- Introduce UART control for remote buzzer operation
