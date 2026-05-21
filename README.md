# Intelligent-Learning-Assessment-System

Coursework project for Electronic System Design. The system is built with
STM32F103C8T6, the STM32 standard peripheral library, and Keil MDK. It monitors
seated posture angle and ambient light, then provides OLED display, buzzer alarm,
LED reminder, and rotary-encoder menu controls.

## Repository Layout

```text
Project/
  Project.uvprojx              Keil MDK project file
  User/main.c                  Main program
  Hardware/                    OLED, MPU6050, ADC, encoder and I/O drivers
  Library/                     STM32F10x standard peripheral library
  Start/                       Startup files and CMSIS support
  System/                      Delay and system helper modules
  README.md                    Detailed wiring, build and test guide
  20231492213 宋佳骏.docx      Coursework report
  论文插图/                    Report figures
tools/
  build_course_paper.py        Report generation helper script
答辩ppt.pptx                   Defense presentation
```

## Quick Start

1. Install Keil MDK 5 and the STM32F1xx Device Family Pack.
2. Open `Project/Project.uvprojx` in Keil.
3. Select `Target 1` and run Rebuild.
4. Download the generated firmware to the STM32F103C8T6 board with ST-Link.

For wiring, module notes, threshold settings and testing steps, see
`Project/README.md`.

## Hardware

- STM32F103C8T6 minimum system board
- 0.96 inch I2C OLED display
- MPU6050 motion sensor
- Photoresistor module
- Rotary encoder module
- Active buzzer module
- LED reminder module
- ST-Link programmer

## Build Status

The latest local Keil build log is stored in `Project/build_release.log`. It
records a successful rebuild with `0 Error(s), 0 Warning(s)`.

## Scope

This repository keeps the core coursework project, source code, report assets and
necessary helper scripts. Large course references, tool installers, Keil build
outputs and temporary generated files are intentionally excluded from version
control.
