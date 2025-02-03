# Embedded Systems Development on STM32L475

This repository contains the source code for an embedded systems project that leverages an **ARM Cortex-M processor**. The project explores fundamental and advanced embedded system concepts, including memory mapping, peripheral control, interrupts, and low-level programming.

## Project Overview

The project follows a structured approach to embedded system development, covering various hardware and software components. The implementation is based on ARM's CMSIS (Cortex Microcontroller Software Interface Standard) and includes functionalities for GPIO, UART communication, memory management, timers, and interrupt handling. The microcontroller used in this project is the **STM32L475**, a low-power ARM Cortex-M4 based MCU.

## Features

- **ARM Cortex-M4 based development**
- **Low-power operation with STM32L475**
- **Low-level peripheral management**
- **Memory-mapped I/O operations**
- **Interrupt-driven processing (NVIC and IRQ handling)**
- **UART communication with IRQ integration**
- **GPIO control and multiplexing**
- **Clock configuration and power management**
- **Execution control through linker scripts**
- **Integration with CMSIS for efficient development**

## Project Structure

```
arm-embedded-project/
├── 📄 .gitignore # Git exclusion rules
├── 📁 .vscode/ # VS Code configuration files
├── 📄 buttons.c / buttons.h # Button input handling (debounce, state machine)
├── 📄 checksum.py # Python script for checksum calculations (CRC, etc.)
├── 📁 clocks/ # Clock configuration and management
│ ├── 📄 clocks.h # Clock initialization and control
│ └── 📄 clocks.o # Compiled clock configuration
├── 📁 CMSIS/ # ARM Cortex Microcontroller Software Interface Standard
│ ├── 📄 core_cm4.h # Cortex-M4 core definitions
│ ├── 📄 arm_math.h # ARM DSP library (math functions)
│ └── ... # Other CMSIS headers
├── 📄 crt0.s # Startup assembly file (reset handler, stack setup)
├── 📄 init.c / init.h # System initialization (peripheral setup, etc.)
├── 📄 irq.c / irq.h # Interrupt handling (ISRs, NVIC configuration)
├── 📄 ld_ram.lds # Linker script for memory mapping (RAM/Flash layout)
├── 📄 led.c / led.h # LED control functions (on/off, blinking, patterns)
├── 📄 main.c # Main application logic (entry point)
├── 📄 matrix.c / matrix.h # Matrix display driver (LED/segment control)
├── 📄 memfuncs.c / memfuncs.h # Memory functions (memcpy, memset, etc.)
├── 📄 uart.c / uart.h # UART communication (TX/RX, baud rate configuration)
├── 📄 Makefile # Build system configuration (compiler flags, targets)
├── 📄 se203.gdb # Debugger configuration (GDB scripts)
└── 📄 README.md # Project documentation (overview, usage, setup)
```

## Key Functionalities

### Memory Mapping

The project includes custom linker scripts to map program sections into memory appropriately. It explores how the ARM Cortex-M processor handles memory layout for stack, heap, and peripherals.

### GPIO Control

The project configures and controls General-Purpose Input/Output (GPIO) pins, enabling features like LED blinking and button interaction. It also implements multiplexing and clock gating for efficient power usage.

### UART Communication

A UART driver is implemented to facilitate serial communication between the ARM processor and external devices. Both polling-based and interrupt-driven transmission methods are included.

### Interrupt Handling

The project integrates Nested Vectored Interrupt Controller (NVIC) functionalities to efficiently process external and internal interrupts, including handling GPIO events, UART reception, and timer-based interrupts.

### Timer and Clock Configuration

System timers and clocks are configured for various operational modes, ensuring optimized performance and low power consumption.

## Building and Running the Project

To build the project, use the provided `Makefile`:

```sh
make
```

After compilation, the generated binary can be loaded onto an STM32L475 microcontroller using a suitable debugger or flashing tool.

## Debugging

Debugging can be performed using GDB and OpenOCD, with the provided se203.gdb configuration file.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments

This project is inspired by coursework from Télécom Paris (SE203), exploring ARM Cortex-M development and embedded systems programming.
