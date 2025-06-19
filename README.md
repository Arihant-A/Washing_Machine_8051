# Washing Machine Controller using AT89S52 Microcontroller

## Overview

This project demonstrates a basic washing machine control system built using the AT89S52 (8051-based) microcontroller. It simulates real-world washing machine functionality including user mode selection, timed operation, motor control, and user feedback via LEDs, buzzer, and a 7-segment display. The project was developed as part of the course "Microprocessor and Microcontroller (23UEC521)" at The LNM Institute of Information Technology, Jaipur.

## Features

* **Wash & Drain Modes**: Selectable using DIP switches
* **User-Defined Timer**: Choose between 1-minute or 2-minute operation
* **7-Segment Display**: Shows remaining operation time
* **LED Indicators**:

  * Red LED for active operation
  * Green LED for completion
* **Buzzer Alert**: Signals when wash or drain cycle is complete
* **Motor Control**:

  * Pump motor runs unidirectionally
  * Main motor alternates direction to simulate agitation

## Hardware Used

* AT89S52 Microcontroller Development Kit
* 1 DC Motor
* 1 Pump Motor
* Motor Driver Circuit (L293D or similar)
* 7-Segment Display (Common Anode)
* Switches (Start, Timer Select, Wash/Drain Mode)
* LEDs (Red and Green)
* Buzzer

## Working Principle

* The user initiates the cycle using the start button.
* Wash or drain mode is selected using switches.
* Timer0 is configured to count down 1 or 2 minutes as set by the user.
* In wash mode, the motor direction alternates every 1.5 seconds to mimic agitation.
* In drain mode, the motor runs in one direction without pump activation.
* At the end of the countdown, all motors stop, green LED lights up, and buzzer sounds.

## Code

The project is programmed in Embedded C using Keil uVision. Interrupt-based Timer0 is used for countdown and delay mechanisms. The lookup table for 7-segment display is defined in the code.

## Flowchart

1. Start
2. Initialize hardware
3. Check for start button
4. Check mode (wash/drain)
5. Set timer based on user input
6. Start Timer0
7. Run motor logic based on mode
8. Countdown and update display
9. On completion, stop motors, sound buzzer, light green LED
10. Wait for next start

## Schematic

A detailed schematic is included showing the connection of all components including microcontroller pins, motors, LEDs, buzzer, switches, and 7-segment display (Designed in Proteus).

## Observations

* Motor LEDs alternate during washing to show direction change.
* Pump LEDs stay active only in wash mode.
* Accurate countdown on the 7-segment display.
* Clear user feedback via LEDs and buzzer.

## Demo

Google Drive Video: [Watch Demo](https://drive.google.com/drive/folders/1XF8qKyP70dnDR9mSEmPnZh9QJ4AQSphG?usp=sharing)

## Conclusion

This project effectively demonstrates the application of microcontrollers in real-time control systems. It integrates hardware and software to perform time-based automated washing operations. The system can be further enhanced with features like water level sensors, load detection, and advanced wash modes.
