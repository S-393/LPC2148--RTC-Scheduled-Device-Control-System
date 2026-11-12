# Menu-Driven RTC Configuration and Scheduled Device Control System

## PROJECT OVERVIEW:

This project implements a Menu-Driven Real-Time Clock (RTC) Configuration and Scheduled Device Control System using the LPC2148 ARM7 microcontroller.

The system displays real-time date and time on a 16×2 LCD. Users can configure RTC settings through a 4×4 matrix keypad and schedule a device to turn ON and OFF at predefined times.

## OBJECTIVES:
- Interface the RTC with the LPC2148 microcontroller.
- Display real-time clock information on a 16×2 LCD.
- Configure date and time using a 4×4 keypad.
- Implement menu-driven navigation.
- Control a device automatically based on scheduled ON and OFF timings.
- Understand peripheral interfacing and embedded C programming.

## HARDWARE REQUIREMENTS:
- LPC2148 ARM7 Development Board
- 16×2 LCD Display
- 4×4 Matrix Keypad
- LED (Device Indicator)
- Switch
- USB-to-UART Interface
- Connecting Wires

## SOFTWARE REQUIREMENTS:
- Keil µVision
- Proteus Design Suite
- Embedded C

## FEATURES:
1. **RTC Display:** Displays current time, date and day on the LCD.
2. **RTC Configuration:** Allows users to modify hours, minutes, seconds, date, month and year.
3. **Menu Navigation:** Provides options for device configuration, RTC settings and exit.
4. **Scheduled Device Control:** Automatically turns the device ON and OFF according to configured timings.
5. **Keypad Interfacing:** Uses a 4×4 matrix keypad for user input.
6. **LCD Interfacing:** Displays menus, RTC information and configuration messages.

## MICROCONTROLLER:
*LPC2148 ARM7
The LPC2148 is an ARM7-based microcontroller used as the main controller of this project.

The microcontroller is responsible for:
1.GPIO control
2.RTC operation
3.LCD interfacing
4.Keypad interfacing
5.External interrupt handling
6.Schedule processing
7.LED/device control


## SYSTEM ARCHITECTURE:
The project follows a modular Embedded C architecture.
The main application communicates with individual peripheral and functionality modules.

## APPLICATION MODULE:
output5.c handles: 
-Main program flow
-Menu system
-RTC display
-RTC configuration
-Schedule configuration
-EINT0 handling
-LED/device control

Driver Modules                    Module	Responsibility
output5.c	                        Main application and menu handling
LCD.c	                            LCD driver
LCD.h	                            LCD function declarations
lcd_defines.h	                    LCD configuration and commands
KPM.c	                            Keypad driver
kpm.h	                            Keypad function declarations
KPM_defines.h	                    Keypad configuration
RTCLOCK.c	                        RTC driver
rtclock.h	                        RTC function declarations
schedule.c	                      Schedule processing
schedule.h	                      Schedule declarations
delay.c	                          Delay functions
delay.h	                          Delay function declarations
defines.h                         Datatypes defines
Startup.s	                        ARM7 startup and vector configuration


## HARDWARE INTERFACE:

The project integrates the LPC2148 with:
1.16×2 LCD
2.4×4 matrix keypad
3.RTC
4.EINT0 configuration switch
5.LED/device output
=>The individual interfaces are controlled through dedicated driver modules.

## LCD INTERFACE:
The project uses a 16×2 LCD in 8-bit mode.

The LCD configuration used by the project is:

LPC2148 Signal	                LCD Signal
P0.8 – P0.15                   	D0 – D7
P0.16                          	RS
P0.17                          	RW
P0.18	                          EN

->LCD Power Connections:
LCD Pin/Signal	                 Connection
VSS	                             GND
VDD	                             VCC

->V0/VEE	Contrast potentiometer:
RS	                            LPC2148
RW	                            LPC2148
EN	                            LPC2148
D0–D7                          	LPC2148

->LCD Control Signals:
Signal	      Full Form	                   Function
RS	        Register Select      	Selects command or data register
RW	        Read/Write         	  Selects read or write operation
EN	        Enable	              Enables LCD data/command transfer

*RS Operation:
RS = 0 → Command
RS = 1 → Data
*RW Operation:
RW = 0 → Write
RW = 1 → Read
*EN Operation
The Enable signal is used to latch the command or data into the LCD.

## 4×4 MATRIX KEYPAD:

A 4×4 matrix keypad is used as the user-input device.
The keypad is used for:
-Menu selection
-Numeric input
-RTC configuration
-Schedule configuration
-Menu navigation
-The keypad driver provides functions for keypad initialization, key detection, and numeric input.

## EINT0 CONFIGURATION SWITCH:
The configuration switch is connected to:

->P0.1 → EINT0:
The switch is used to enter the configuration menu.
When the switch is pressed, the EINT0 interrupt is generated.

The interrupt service routine sets the menu request flag:
menu_request = 1

The main loop then detects this flag and opens the configuration menu.
The complete menu processing is not performed inside the ISR.

This keeps the ISR short and allows the main application to handle LCD and keypad operations.


## REAL-TIME CLOCK:
The LPC2148 internal RTC maintains:
-Hour
-Minute
-Second
-Date
-Month
-Year
-Day of week

The RTC is used for two main purposes:
1.Displaying the current date and time.
2.Providing the current time for schedule comparison.

## RTC Time:
The RTC time format is:
HH:MM:SS
Example:
14:25:36

Valid Time Range
Parameter	Valid Range
Hour	0–23
Minute	0–59
Second	0–59
The entered values are validated before updating the RTC.

## RTC Date:
The RTC date format is:
DD/MM/YYYY
Example:
02/10/2026

The project validates the entered date according to the selected month and year.

## RTC Day:
The project uses the following day mapping:
Key	Day
0	Sunday
1	Monday
2	Tuesday
3	Wednesday
4	Thursday
5	Friday
6	Saturday
7	Back

 ## Menu System:
The project uses a hierarchical menu system for RTC and schedule configuration.

Main Menu
1.RTC  2.SCH
3.EXIT

## 1.RTC
Opens the RTC configuration menu.

## 3.EXIT
Exits the configuration menu and returns to normal system operation.

## RTC Menu
The RTC menu is:

1.TIME 2.DATE
3.DAY  4.BACK
1.TIME
Opens the time configuration menu.

2.DATE
Opens the date configuration menu.

3.DAY
Opens the day selection menu.

4.BACK
Returns directly to the main menu.

## TIME Menu
The Time menu is:

1.HR 2.MIN
3.SEC 4.BACK

1.HR
Sets the RTC hour.
Valid range:
0–23

2.MIN
Sets the RTC minute.
Valid range:
0–59

3.SEC
Sets the RTC second.
Valid range:
0–59

4.BACK
Returns to the RTC menu.

## DATE Menu
The Date menu is:

1.DATE 2.MONTH
3.YEAR 4.BACK
1.DATE
Sets the RTC date.

2.MONTH
Sets the RTC month.
Valid range:
1–12

3.YEAR
Sets the RTC year.

4.BACK
Returns to the RTC menu.

## DAY Menu
All day options are displayed together:

0S 1M 2T 3W
4T 5F 6S 7B
Where:
Key	Function
0	Sunday
1	Monday
2	Tuesday
3	Wednesday
4	Thursday
5	Friday
6	Saturday
7	Back

Selecting 0–6 updates the RTC day.
Selecting 7 returns to the RTC menu.

## 2.SCH
Opens the schedule configuration menu.
 Schedule Menu.
 
1.ON  2.OFF
3.BACK

The schedule contains:
ON Hour
ON Minute
OFF Hour
OFF Minute

-> ON Menu
The ON menu is:
1.HR 2.MIN
3.BACK
The user can configure:
ON Hour
ON Minute

-> OFF Menu
The OFF menu is:
1.HR 2.MIN
3.BACK
The user can configure:
OFF Hour
OFF Minute

## Schedule Operation
The current RTC time is continuously compared with the configured ON and OFF times.

The schedule supports two cases:
1.Normal same-day schedule
2.Midnight-crossing schedule

1.Normal Schedule
When: ON TIME < OFF TIME
Example:
ON = 09:00
OFF = 17:00
The device is active when:
ON_TIME ≤ CURRENT_TIME < OFF_TIME
->Expected Operation
Current Time	Device
08:59	OFF
09:00	ON
12:00	ON
16:59	ON
17:00	OFF
17:01	OFF

*The ON boundary is included.
*The OFF boundary is excluded.

## Midnight-Crossing Schedule
The project also supports schedules where:
ON TIME > OFF TIME
Example:
ON = 22:00
OFF = 06:00
The device operates from 22:00 through midnight and continues until 06:00.
->Expected Operation
Current Time	Device
21:59	OFF
22:00	ON
23:59	ON
00:00	ON
05:59	ON
06:00	OFF

*This is handled using separate schedule comparison logic for the midnight-crossing condition.

Same ON/OFF Time
If: ON TIME = OFF TIME
the schedule is rejected.

Example:
ON = 09:00
OFF = 09:00
Expected result:
SAME TIME

*The user must configure different ON and OFF times.

->Input Validation
The project validates all important user inputs before updating the RTC or schedule.
Time Validation
Parameter	Valid Range
Hour	0–23
Minute	0–59
Second	0–59
Month Validation
Parameter	Valid Range
Month	1–12
Day Validation
Parameter	Valid Range
Day	0–6

-> Date Validation
The maximum number of days depends on the selected month.
Month	Maximum Days
January	31
February	28/29
March	31
April	30
May	31
June	30
July	31
August	31
September	30
October	31
November	30
December	31
Examples:

Date	Result
30/04	Valid
31/04	Invalid
28/02	Valid
29/02	Depends on leap year

->Leap-Year Validation
The project checks whether the selected year is a leap year before accepting February 29.

The standard leap-year condition is:

(year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))

Examples:

Year	Result
2000	Leap Year
2024	Leap Year
2028	Leap Year
2100	Not a Leap Year

EINT0 Interrupt Handling
The EINT0 interrupt is used only to request entry into the configuration menu.

The ISR performs the following operations:

Set menu_request.
Clear the external interrupt.
Return from the interrupt.
The main application performs:

Check menu_request.
Open the main menu.
Process keypad input.
Configure RTC or schedule.
Return to normal operation.
This approach avoids lengthy processing inside the interrupt service routine.

## Main Application Flow
The main application performs the following operations:

-Initialize LCD.
-Initialize RTC.
-Initialize keypad.
-Initialize LED/device.
-Initialize EINT0.
-Enter the main loop.
-Display current RTC information.
-Read current RTC time.
-Check the programmed schedule.
-Control the LED/device.
-Check the menu request flag.
-Open the configuration menu if requested.
-Return to normal operation.

## Software Modules
output.c
Responsible for the main application.

Functions include:
-Menu handling
-RTC display
-RTC configuration
-Schedule configuration
-EINT0 initialization
-EINT0 ISR
-LED/device control
-Main application loop
-LCD.c

->Responsible for LCD operations.
Functions include:
-LCD initialization
-Sending commands
-Sending data
-Displaying strings
-Displaying numbers
-KPM.c

->Responsible for keypad operations.
Functions include:
-Keypad initialization
-Key scanning
-Numeric input
-RTCLOCK.c

->Responsible for RTC operations.
Functions include:
-RTC initialization
-Setting time
-Reading time
-Setting date
-Reading date
-Setting day
-Reading day
-schedule.c

->Responsible for schedule processing.
Functions include:
-Setting ON/OFF schedule
-Converting time for comparison
-Checking whether the schedule is active
-Supporting midnight-crossing schedules
-delay.c
-Provides required software delay functions.

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

## PROJECT IMAGES 
->HARDWARE:
hardware/.blockdiagram.jpeg
hardware/.Hardware.png

->PROTEUS
proteus/.LPC2148 RTC Schedules Control Flowchart.png
proteus/.

## Applications

- Scheduled electrical device control
- RTC-based automation
- Embedded systems learning
- ARM7 peripheral interfacing

## Conclusion

This project demonstrates the implementation of an RTC-based scheduled device control system using the LPC2148 microcontroller. It provides practical experience with Embedded C programming, LCD interfacing, keypad interfacing, RTC configuration, GPIO and interrupt handling.

---

**Developed using LPC2148 ARM7 Microcontroller and Embedded C.**
