# About

Intelligent-Learning-Assessment-System is an embedded coursework project for
learning-space monitoring. It combines posture sensing, ambient-light detection,
local display, alarm output and menu interaction on an STM32F103C8T6 platform.

The project is intended to demonstrate a complete small embedded system rather
than a single isolated driver. It covers hardware connection, sensor acquisition,
threshold judgment, user feedback and Keil-based firmware delivery.

## What It Does

- Measures posture-related motion data with an MPU6050 sensor.
- Samples ambient light through an analog photoresistor module.
- Displays status and settings on an I2C OLED screen.
- Provides buzzer and LED reminders when monitored values exceed configured
  thresholds.
- Uses a rotary encoder for simple local parameter adjustment.

## Technical Scope

- MCU: STM32F103C8T6
- IDE: Keil MDK 5
- Firmware library: STM32F10x Standard Peripheral Library
- Main language: C
- Deliverables: firmware project, report, presentation and supporting figures

## Repository Policy

The repository keeps the coursework source, documentation and final deliverables.
Large reference packages, installers, temporary generated files and Keil build
artifacts are excluded so the Git history stays focused and practical.
