# Menu-Driven RTC Configuration and Scheduled Device Control System

## Project Overview

This project implements a Menu-Driven Real-Time Clock (RTC) Configuration and Scheduled Device Control System using the LPC2148 ARM7 microcontroller.

The system displays real-time date and time on a 16×2 LCD. Users can configure RTC settings through a 4×4 matrix keypad and schedule a device to turn ON and OFF at predefined times.

## Objectives

- Interface the RTC with the LPC2148 microcontroller.
- Display real-time clock information on a 16×2 LCD.
- Configure date and time using a 4×4 keypad.
- Implement menu-driven navigation.
- Control a device automatically based on scheduled ON and OFF timings.
- Understand peripheral interfacing and embedded C programming.

## Hardware Requirements

- LPC2148 ARM7 Development Board
- 16×2 LCD Display
- 4×4 Matrix Keypad
- LED (Device Indicator)
- Switch
- USB-to-UART Interface
- Connecting Wires

## Software Requirements

- Keil µVision
- Proteus Design Suite
- Embedded C

## Features

1. **RTC Display:** Displays current time, date and day on the LCD.
2. **RTC Configuration:** Allows users to modify hours, minutes, seconds, date, month and year.
3. **Menu Navigation:** Provides options for device configuration, RTC settings and exit.
4. **Scheduled Device Control:** Automatically turns the device ON and OFF according to configured timings.
5. **Keypad Interfacing:** Uses a 4×4 matrix keypad for user input.
6. **LCD Interfacing:** Displays menus, RTC information and configuration messages.

## Project Working

1. On startup, the LCD displays the current RTC time and date.
2. When the configuration switch is pressed, the main menu is displayed.
3. The user can select device configuration or RTC configuration.
4. RTC values can be modified using the keypad.
5. The user can configure scheduled device ON and OFF timings.
6. The LPC2148 continuously monitors the RTC and controls the device according to the configured schedule.

## Peripheral Interfacing

- **RTC:** Maintains current time and date.
- **LCD:** Displays RTC information and menu options.
- **Keypad:** Accepts user input.
- **GPIO:** Controls the device indicator.
- **External Interrupt:** Detects the configuration switch press.

## Project Structure

```text
LPC2148-RTC-Scheduled-Device-Control/
│
├── Source/
│   ├── output5.c
│   ├── schedule.c
│   ├── schedule.h
│   ├── Rtclock.c
│   ├── Rtclock.h
│   ├── LCD.c
│   ├── LCD.h
│   ├── LCD_defines.h
│   ├── KPM.c
│   ├── KPM.h
│   ├── KPM_defines.h
│   ├── delay.c
│   ├── delay.h
│   └── defines.h
│
├── Proteus/
│
├── Hardware/
│
└── README.md
```

## Applications

- Scheduled electrical device control
- RTC-based automation
- Embedded systems learning
- ARM7 peripheral interfacing

## Conclusion

This project demonstrates the implementation of an RTC-based scheduled device control system using the LPC2148 microcontroller. It provides practical experience with Embedded C programming, LCD interfacing, keypad interfacing, RTC configuration, GPIO and interrupt handling.

---

**Developed using LPC2148 ARM7 Microcontroller and Embedded C.**
