# Hardware Guide

This document lists the recommended hardware modules for the Intelligent Learning Assessment System.

## Main Controller

| Item | Recommendation | Notes |
| --- | --- | --- |
| MCU board | STM32F103C8T6 minimum system board | Commonly known as Blue Pill. |
| Programmer | ST-Link V2 | Used for SWD programming and debugging. |
| Power | USB or stable 5V/3.3V supply | Follow the board power input requirements. |

## Sensor and Output Modules

| Module | Purpose | Interface |
| --- | --- | --- |
| MPU6050 | Posture angle sensing | Software I2C on PB10/PB11 |
| Photoresistor module | Ambient light sensing | Analog output to PA0 ADC |
| 0.96 inch OLED display | Real-time display | Software I2C on PB8/PB9 |
| Rotary encoder | Menu navigation and parameter setting | PA1/PA2/SW on PA3 |
| Active buzzer module | Posture alarm | PB12 output |
| LED module | Low-light reminder | PB13 output |

## Recommended Accessories

- Dupont wires.
- Breadboard or soldered prototype board.
- USB cable or stable external power supply.
- Optional multimeter for voltage and continuity checks.

## Voltage Notes

- The STM32F103 works at 3.3V logic.
- OLED and MPU6050 modules are recommended to be powered from 3.3V unless your specific module documentation states otherwise.
- The ADC input PA0 must not receive a voltage higher than 3.3V.
- If a module is powered from 5V, confirm that its signal output is safe for STM32 input pins.

## Module Selection Notes

### OLED

Use a common 0.96 inch I2C OLED display. The current OLED driver is designed for typical I2C OLED modules and uses PB8/PB9.

### MPU6050

Use an MPU6050 accelerometer and gyroscope module. The current firmware reads accelerometer data and calculates a posture angle from the configured axis.

### Photoresistor Module

Use the analog output pin `AO`, not only the digital output pin `DO`. The firmware samples the light value through ADC on PA0.

### Buzzer and LED

The current firmware assumes a low-level active buzzer and a low-level active LED module. If your module is high-level active, update the corresponding output logic in the firmware.