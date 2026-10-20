# Embedded-M04 ⚡

<p align="center">
  <img src="assets/atmega328p.png" alt="ATmega328P board illustration" width="330" height="170" style="border-radius: 12px;" />
</p>

This module introduces external interrupts and the event-driven programming model used in embedded systems. Instead of polling continuously, the microcontroller reacts immediately when a hardware event occurs such as a rising or falling edge on an input pin.

The main objective is to understand interrupt sources, mask registers, flag handling, and the logic behind responsive embedded applications.

## What you learn 🧠

This repository introduces the core concepts of interrupt-driven AVR programming:

- External interrupt configuration
- GPIO input setup for switch detection
- Edge-sensitive event handling
- Interrupt masks and flag clearing
- Re-enabling interrupts after a service routine
- Event-driven firmware design on AVR

## Project setup 🛠️

This repository contains several small exercises under separate folders such as `ex00` and `ex01`.

Each exercise shows how a button press or hardware event can trigger a state change without a continuous polling loop.

## Build commands 🔧

From the project root, you can compile an exercise with:

```bash
make -C ex00 hex
```

To flash the firmware to the board:

```bash
make -C ex00 flash
```

To build and flash in one step:

```bash
make -C ex00 all
```

To clean generated build files:

```bash
make -C ex00 clean
```

If you are inside the exercise folder itself, the commands are simply:

```bash
make hex
make flash
make all
make clean
```

## Required tools 🧰

You need the AVR toolchain installed on your machine:

- `avr-gcc`
- `avr-libc`
- `avr-objcopy`
- `avrdude`

On Debian/Ubuntu-based systems:

```bash
sudo apt update
sudo apt install gcc-avr avr-libc avrdude
```

## Hardware used 🖥️

This project targets an ATmega328P-based board, typically an Arduino-compatible board.

Typical hardware components:

- ATmega328P microcontroller
- Push button or tactile switch
- LED or output device driven by interrupt logic
- Pull-up or pull-down resistor configuration
- USB programming interface

## Useful resources 📚

- ATmega328P datasheet: https://www.microchip.com/en-us/product/ATmega328P
- AVR libc documentation: https://www.nongnu.org/avr-libc/user-manual/
- AVR-GCC toolchain: https://gcc.gnu.org/wiki/avr-gcc
- avrdude documentation: https://github.com/avrdudes/avrdude

## Notes 📝

- Interrupt service routines must be short and efficient to avoid blocking the main flow of the program.
- Proper edge configuration and flag clearing are essential to prevent repeated trigger events.
- This module introduces the usual embedded pattern: configure hardware, enable interrupts, then keep the main loop simple.
