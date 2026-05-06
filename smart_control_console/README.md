# STM32 Template for Nucleo-F103RB

A clean STM32CubeMX source template for the STM32 Nucleo-F103RB (`STM32F103RBT6`).

This repository is intended to be used as a starting point for new STM32 projects. It keeps the common board configuration and generated HAL/CMSIS source tree, while removing application-specific demo logic and excluding STM32CubeIDE project metadata that would otherwise lock the template to a fixed project identity.

## Template Baseline
- Board: STM32 Nucleo-F103RB
- MCU: STM32F103RBT6
- Development environment: macOS + STM32CubeIDE + STM32CubeMX
- System clock source: `HSI`
- User LED GPIO: `PA5`
- UART peripheral: `USART2`
- UART TX: `PA2`
- UART RX: `PA3`
- UART configuration: `115200 8N1`

## Included in the Template
- `Core/` source tree
- `Drivers/` HAL and CMSIS source tree
- Basic system clock initialization
- `GPIOA` enable and `PA5` output initialization
- `USART2` initialization
- Startup file and linker script
- Empty application skeleton in `main.c`
- CubeMX configuration file `smart_control_console.ioc`

## Intentionally Excluded
- `.project`
- `.cproject`
- `.mxproject`
- `.settings/`
- `*.launch`
- Generated build folders such as `Debug/`, `Release/`, and `build/`

These files are excluded on purpose so a new project can be regenerated with its own project name and IDE metadata.

## Repository Structure
```text
.
├── Core/
├── Drivers/
├── STM32F103RBTX_FLASH.ld
├── smart_control_console.ioc
├── RENAME_PROJECT.md
├── .gitignore
└── README.md
```

## How to Use This Template
1. Create a new repository from this template or clone it locally.
2. Rename `smart_control_console.ioc` to your target project name if needed.
3. Open the `.ioc` file in STM32CubeMX or STM32CubeIDE.
4. Change the project name in CubeMX project settings.
5. Regenerate the STM32CubeIDE project files.
6. Open the regenerated project in STM32CubeIDE and build it.

## Recommended Workflow
1. Start from the `.ioc` file, not from pre-generated IDE metadata.
2. Let STM32CubeMX or STM32CubeIDE regenerate `.project`, `.cproject`, `.settings/`, and launch files for the new project name.
3. Add application code only inside `USER CODE` sections or separate user modules.
4. Commit the regenerated project metadata in the new project repository if your team wants to version them.

## Where to Add Application Code
- Startup initialization: `Core/Src/main.c` inside `USER CODE BEGIN 2`
- Main loop logic: `Core/Src/main.c` inside `USER CODE BEGIN 3`
- User modules: create additional files under `Core/` or your own module folders

## Notes
- This template intentionally keeps `USART2` and `PA5` configured because they are useful for early bring-up and diagnostics.
- If your new project uses different peripherals or pins, update the `.ioc` first and then regenerate code.
