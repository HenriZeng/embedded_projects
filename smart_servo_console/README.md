# STM32 Smart Servo Console

**Version: V1.0**

## 1. Project Title
STM32 Smart Servo Console - SG90 Servo Control System

## 2. Project Overview
This project implements a complete SG90 servo motor control system on the STM32 Nucleo-F103RB. It uses a potentiometer to control the servo angle (0-180°) through ADC sampling and PWM output. The system provides real-time feedback via UART for monitoring and debugging.

## 3. Hardware Information
- Development board: STM32 Nucleo-F103RB
- MCU: STM32F103RBT6
- Development environment: macOS, STM32CubeIDE, STM32CubeMX
- ADC peripheral: `ADC1`
- ADC input channel: `ADC_CHANNEL_0`
- Analog input pin: `PA0` (ADC1_IN0)
- Input device: Potentiometer (0-3.3V range)
- PWM timer: `TIM3`
- PWM channel: `CH1`
- PWM output pin: `PA6` (TIM3_CH1)
- Servo motor: SG90 (or compatible)
- UART peripheral: `USART2`
- UART TX pin: `PA2`
- UART RX pin: `PA3`
- Baud rate: `115200`
- Supply voltage: `3.3V` (logic), `5V` (servo power)
- Typical host connection: ST-LINK Virtual COM Port
- Debug/download interface: ST-LINK onboard programmer/debugger

## 4. System Architecture

### Control Flow
```
Potentiometer (0-3.3V)
    ↓
ADC Sampling (PA0)
    ↓
ADC Value (0-4095)
    ↓
Angle Conversion (0-180°)
    ↓
Pulse Width Calculation (500-2500us)
    ↓
PWM Output (PA6)
    ↓
SG90 Servo Motor
```

### PWM Configuration
```
Timer: TIM3
Prescaler: 71 (8MHz / 72 = 1MHz timer clock)
Period: 19999 (20ms = 50Hz PWM frequency)
Resolution: 1us per tick

Servo Timing:
- 0°   → 500us  pulse width
- 90°  → 1500us pulse width
- 180° → 2500us pulse width
```

## 5. Features

### Core Features
- Potentiometer-based servo angle control
- Real-time ADC sampling (12-bit resolution)
- Precise PWM generation for servo control
- UART debug output with printf support
- Smooth servo movement

### Technical Features
- Software-triggered ADC conversion
- Polling mode ADC readout
- 50Hz PWM frequency (standard for servos)
- 1us PWM resolution
- Angle range: 0-180 degrees
- Update rate: 10Hz (100ms loop)

## 6. Hardware Connections

```
STM32 Nucleo-F103RB Connections:

Potentiometer:
├── Pin 1 → GND
├── Pin 2 (Wiper) → PA0 (ADC input)
└── Pin 3 → 3.3V

SG90 Servo:
├── Brown Wire  → GND
├── Red Wire    → 5V (external power recommended)
└── Orange Wire → PA6 (PWM signal)

UART (ST-LINK Virtual COM):
├── TX → PA2
└── RX → PA3

Important Notes:
- Servo power (5V) should come from external supply
- Do NOT power servo from 3.3V pin
- Common ground between STM32 and servo power
```

## 7. How to Use

### Build and Flash

1. Open the project in STM32CubeIDE
2. Build the project (Ctrl+B)
3. Flash to Nucleo-F103RB
4. Connect hardware as described above

### Serial Monitor Setup

- Baud rate: `115200`
- Data bits: `8`
- Parity: `None`
- Stop bits: `1`
- Flow control: `None`

### Expected Output

**Startup Message:**
```
========================================
  Smart Servo Console V1.0
  SG90 Servo Control System
========================================
Initializing...
[OK] PWM started on TIM3 CH1 (PA6)
[OK] Servo initialized to 90 degrees
System ready!
========================================
Format: ADC:xxxx ANGLE:xxx PULSE:xxxx
========================================
```

**Runtime Output:**
```
ADC:   0 ANGLE:  0 PULSE: 500
ADC:1024 ANGLE: 45 PULSE:1000
ADC:2048 ANGLE: 90 PULSE:1500
ADC:3072 ANGLE:135 PULSE:2000
ADC:4095 ANGLE:180 PULSE:2500
```

### Operation

1. Power on the system
2. Observe servo moves to center position (90°)
3. Rotate potentiometer
4. Watch servo follow potentiometer position
5. Monitor UART output for real-time data

## 8. Key Technical Points

### ADC Implementation
- Software-triggered conversion
- Polling-based readout
- 12-bit resolution (0-4095)
- Single-channel mode
- Conversion time: ~55 ADC cycles

### PWM Implementation
- Timer frequency: 1MHz (1us resolution)
- PWM frequency: 50Hz (20ms period)
- Pulse width range: 500-2500us
- Duty cycle range: 2.5%-12.5%

### Servo Control Algorithm
```c
// ADC to Angle conversion
angle = (adc_value * 180) / 4095

// Angle to Pulse conversion
pulse_us = 500 + (angle * 2000) / 180

// PWM update
__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse_us)
```

### Code Organization
- `__io_putchar()`: Printf redirection to UART
- `Read_ADC_Value()`: ADC sampling function
- `ADC_To_Angle()`: ADC to angle conversion
- `Servo_Angle_To_Pulse()`: Angle to PWM pulse conversion
- Main loop: Control logic with 10Hz update rate

## 9. Project Highlights

### Engineering Excellence
- Clean and well-documented code
- Modular function design
- Proper error handling
- Real-time feedback system

### Practical Applications
- Servo motor control learning
- PWM signal generation reference
- ADC sampling demonstration
- Embedded control system example

### Learning Value
- ADC peripheral usage
- PWM generation techniques
- Servo motor control principles
- Real-time embedded systems

## 10. Troubleshooting

### Servo Not Moving
- Check power supply (5V for servo)
- Verify PWM signal on PA6 with oscilloscope
- Ensure common ground connection
- Check servo is not damaged

### Erratic Servo Movement
- Add capacitor (100uF) across servo power
- Use external 5V power supply
- Check for loose connections
- Reduce update rate if needed

### No UART Output
- Verify baud rate (115200)
- Check USB cable connection
- Ensure correct COM port selected
- Verify printf redirection code

### ADC Reading Issues
- Check potentiometer connections
- Verify PA0 is configured as analog input
- Ensure potentiometer voltage is 0-3.3V
- Test with multimeter

## 11. Calibration

### Servo Calibration
If your servo doesn't reach full range:

```c
// Adjust pulse width limits in Servo_Angle_To_Pulse()
// Some servos may need:
// 0°   → 400us  or 600us
// 180° → 2400us or 2600us

uint32_t pulse_us = MIN_PULSE + (angle * PULSE_RANGE) / 180;
```

### ADC Calibration
For better accuracy:

```c
// Add offset and gain correction
uint32_t calibrated_adc = (raw_adc - offset) * gain / 1000;
```

## 12. Possible Extensions

### Near-term Extensions
- Add button for preset positions
- Implement smooth acceleration/deceleration
- Add LED indicator for servo status
- Support multiple servo control

### Advanced Extensions
- Add UART command interface
- Implement position feedback (if using feedback servo)
- Add speed control parameter
- Create servo sequencer for patterns

### System Optimization
- Use timer interrupt for smoother control
- Implement PID control for precision
- Add low-pass filter for ADC readings
- Support different servo types

## 13. Technical Specifications

### System Performance
- Control resolution: 180 steps (1° per step)
- Update rate: 10Hz (100ms)
- ADC resolution: 12-bit (4096 steps)
- PWM resolution: 1us (2000 steps for servo range)
- Response time: <100ms

### Power Requirements
- MCU: 3.3V @ ~50mA
- Servo (SG90): 5V @ 100-250mA (load dependent)
- Total: 5V @ 150-300mA typical

### Timing Specifications
- PWM period: 20ms (50Hz)
- Pulse width: 500-2500us
- ADC conversion: ~10us
- Loop period: 100ms

## 14. Safety Notes

⚠️ **Important Safety Information**

1. **Power Supply**
   - Never power servo from 3.3V pin
   - Use external 5V supply for servo
   - Ensure adequate current capacity (>500mA)

2. **Connections**
   - Always connect ground first
   - Verify polarity before powering on
   - Use proper wire gauge for servo power

3. **Operation**
   - Do not stall servo for extended periods
   - Allow servo to cool if it gets hot
   - Do not exceed mechanical limits

## 15. License and Credits

**Project:** Smart Servo Console  
**Version:** V1.0  
**Status:** Production Ready ✅

**Copyright:** © 2026 STMicroelectronics  
**License:** Provided AS-IS

---

**Complete SG90 Servo Control System**  
**Ready for Learning and Development** 🎯
