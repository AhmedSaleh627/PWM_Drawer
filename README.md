# PWM Drawer

This project implements a PWM (Pulse Width Modulation) Drawer that functions as a mini oscilloscope, capable of displaying the frequency and waveform of the generated PWM signal. It also allows for the control of the signal's duty cycle. The device uses an LCD to show the duty cycle, frequency, and other related information in real-time.

## Features

- Displays the duty cycle, frequency, and waveform of the PWM signal on an LCD.
- Allows adjustment of the duty cycle via external interrupts.
- Implements a hardware input capture unit (HW ICU) for precise timing measurements.

## Components

- Microcontroller (e.g., ATmega328P)
- LCD Display
- External Interrupt Buttons
- PWM Output Pin

## Hardware Connections

- Connect the LCD display to the microcontroller according to the pin configuration in `LCD_config.h`.
- Connect external interrupt buttons to the appropriate interrupt pins (e.g., INT0 and INT1).
- Connect the PWM output pin (PORTB, PIN3) to the desired output device (e.g., an LED or motor driver).

## Software Requirements

- AVR-GCC Compiler
- AVRDUDE for programming the microcontroller
- A suitable IDE (e.g., Atmel Studio, Arduino IDE, or any text editor)


