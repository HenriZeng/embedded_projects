# STM32 ADC OLED Monitor

## 1. Project Title
STM32 ADC OLED Monitor

## 2. Project Overview
This project implements a real-time analog signal monitoring system on the STM32 Nucleo-F103RB. It samples analog voltage through `ADC1`, converts the data to millivolts, and displays real-time ADC values and voltage readings on an SSD1306 OLED display over I2C.

## 3. Hardware Information
- Development board: STM32 Nucleo-F103RB
- MCU: STM32F103RBT6
- Development environment: macOS, STM32CubeIDE, STM32CubeMX
- ADC peripheral: `ADC1`
- ADC input channel: `ADC_CHANNEL_0`
- Analog input pin: `PA0`
- Display: SSD1306 OLED (128x64, I2C)
- I2C peripheral: `I2C1`
- I2C SCL pin: `PB8` (Arduino D15)
- I2C SDA pin: `PB9` (Arduino D14)
- Supply voltage: `3.3V`
- Debug/download interface: ST-LINK onboard programmer/debugger

## 4. Features
- Real-time ADC value display
- Real-time voltage display in millivolts
- Continuous refresh on OLED
- Stable readings when input is defined (GND / 3.3V)
- Demonstrates floating input behavior with unstable readings
- Integration of sensor input and display output

## 5. System Behavior
- ADC samples analog voltage from `PA0`
- Data is converted to millivolts using 12-bit ADC resolution
- OLED displays real-time ADC value and voltage
- System continuously updates display in main loop

## 6. How to Use
1. Open the project in STM32CubeIDE.
2. Build and flash the firmware to the Nucleo-F103RB.
3. Connect the SSD1306 OLED display to I2C pins `PB8` (SCL) and `PB9` (SDA).
4. Connect an analog signal source to `PA0` within the valid ADC input range (0-3.3V).
5. Reset or run the board.
6. Observe the real-time ADC value and voltage on the OLED display.

Example readings:

```text
When PA0 is connected to:
- GND   → ADC ≈ 0    → Voltage ≈ 0 mV
- 3.3V  → ADC ≈ 4095 → Voltage ≈ 3300 mV
- Float → Unstable readings (expected behavior)
```

## 7. Hardware Notes
- Floating ADC input results in unstable values due to noise pickup
- A pull-down resistor (10kΩ - 100kΩ) is recommended for stable measurements when no signal is connected
- OLED requires correct I2C address configuration (typically `0x3C` or `0x3D`)
- Verify I2C pull-up resistors are present (usually built into OLED module)

## 8. Key Technical Points
- ADC single-channel sampling on `PA0`
- 12-bit ADC resolution with voltage conversion to millivolts
- I2C communication with SSD1306 OLED controller
- Frame buffer-based display rendering
- Periodic refresh loop for continuous monitoring
- Integration of analog sensor input and I2C display output

## 9. Project Highlights
- Clear example of ADC-to-display data pipeline
- Practical reference for real-time sensor monitoring with visual feedback
- Demonstrates I2C peripheral usage for external display control
- Suitable foundation for multi-channel monitoring, data logging, or sensor dashboards

## 10. Possible Extensions
- Add multiple ADC channels for multi-signal monitoring
- Implement min/max/average statistics display
- Add graphical waveform plotting on OLED
- Introduce threshold alarms with visual indicators
- Support user calibration or offset adjustment
- Add UART logging for remote monitoring alongside local display
