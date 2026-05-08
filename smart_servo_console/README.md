# STM32 Smart Servo Console

## Overview
`smart_servo_console` is a low-latency potentiometer-to-servo control project for the STM32 Nucleo-F103RB.

This final version is tuned for responsive manual control:

- system clock: `8 MHz` HSI
- servo PWM: `50 Hz`
- servo pulse range: `500 us` to `2500 us`
- ADC low-pass filtering enabled
- ADC deadband enabled
- PWM deadband enabled
- OLED display disabled in normal use
- UART status output disabled in normal use

The default runtime path is intentionally minimal so the servo stays as "follow-hand" as possible.

## Hardware
- Board: `STM32 Nucleo-F103RB`
- MCU: `STM32F103RBT6`
- Potentiometer input: `PA0` (`ADC1_IN0`)
- Servo PWM output: `PA6` (`TIM3_CH1`)
- User button: `PC13`

## Wiring
### Potentiometer
- one side to `GND`
- wiper to `PA0`
- other side to `3.3V`

### Servo
- signal to `PA6`
- VCC to external `5V`
- GND to external power ground
- STM32 `GND` must be tied to the same external ground

## Runtime Behavior
On power-up the firmware:

1. initializes GPIO, ADC and TIM3
2. starts PWM on `PA6`
3. sets the servo to center
4. enters continuous potentiometer tracking mode

The main loop runs a light control path:

- sample ADC
- apply low-pass filter
- ignore small ADC jitter with a deadband
- map filtered value to angle
- map angle to pulse width
- ignore tiny pulse-width changes
- update TIM3 compare value

This is what removed the visible "hunting" and small-signal twitching during testing.

## Timing and Control Parameters
### Clock and PWM
- timer source clock: `8 MHz`
- TIM3 prescaler: `7`
- TIM3 period: `19999`
- PWM tick: `1 us`
- PWM period: `20 ms`
- PWM frequency: `50 Hz`

### Servo Range
- `0° -> 500 us`
- `90° -> 1500 us`
- `180° -> 2500 us`

### Stability Tuning
- control period: `2 ms`
- ADC filter shift: `3`
- ADC deadband: `12`
- pulse deadband: `8 us`

## Manual Scan Mode
For maintenance and travel testing, hold the `USER` button while powering on.

The firmware enters a manual pulse scan mode that steps through fixed pulse widths each time the button is pressed:

- `700`
- `800`
- `900`
- `1100`
- `1300`
- `1500`
- `1700`
- `1900`
- `2100`
- `2200`
- `2300`

This mode is kept in the final code as a service tool, but it is not used during normal control.

## Build and Flash
1. Open the project in `STM32CubeIDE`
2. Build the project
3. Flash it to the Nucleo board
4. Connect the potentiometer and servo as listed above

## Notes
- Do not power the servo from `3.3V`
- External `5V` servo power is strongly recommended
- Common ground is mandatory
- If twitching returns, check grounding and servo power first
- If you want even more stability, slightly increase `SERVO_ADC_DEADBAND`
- If you want slightly more sensitivity, slightly decrease `SERVO_ADC_DEADBAND`
