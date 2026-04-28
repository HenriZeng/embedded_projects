# Embedded Projects

STM32 embedded learning projects based on STM32 Nucleo-F103RB.

## Development Environment

- Board: STM32 Nucleo-F103RB
- MCU: STM32F103RBT6
- OS: macOS
- IDE: STM32CubeIDE
- Configuration Tool: STM32CubeMX

## New Project Workflow

New STM32 projects in this workspace are created from an external template repository instead of copying an existing project manually.

- Template repository: `/Users/henri/git/stm32-template-f103rb-base`
- Project creation script: `/Users/henri/STM32CubeIDE/workspace_2.1.1/new_stm32_project.sh`

### Create a New Project

```bash
./new_stm32_project.sh motor_driver
```

The script will:

- Copy the template repository into this workspace
- Create a new project folder using the target project name
- Remove copied Git-related files such as `.git` and `.gitignore`
- Rename `stm32_template.ioc` to the new project name
- Update project name references in `README.md` and `RENAME_PROJECT.md`

### After Running the Script

You still need to:

1. Open the new `.ioc` file in STM32CubeIDE or STM32CubeMX
2. Confirm the `Project Name` matches the new project name
3. Regenerate STM32CubeIDE project files
4. Build and verify the project

## Projects

### 1. led_blink

Basic GPIO output demo.

Features:

- Configure PA5 as GPIO output
- Toggle LD2 LED periodically

### 2. uart_test

Basic UART transmission demo.

Features:

- Configure USART2 at 115200 baud rate
- Send text from STM32 to Mac serial terminal
- Verify UART TX communication

### 3. uart_led_shell

UART-based LED command shell.

Features:

- Receive commands from serial terminal
- Control LD2 LED with commands
- Supported commands:
  - `ON`
  - `OFF`
  - `TOG`
  - `STATUS`
  - `HELP`
- Case-insensitive command parsing
- CR/LF-based command termination
