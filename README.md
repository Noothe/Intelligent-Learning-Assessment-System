# Intelligent Learning Assessment System

Intelligent Learning Assessment System is an open-source embedded monitoring system based on STM32F103, MPU6050 and OLED. It monitors sitting posture angle and ambient light, provides real-time feedback through buzzer, LED and display, and can be used as a learning-assistance or posture-reminder device.

智能学习监测系统是一个基于 STM32F103、MPU6050 和 OLED 的开源嵌入式监测系统。它可以监测坐姿前倾角度和环境光照，并通过蜂鸣器、LED 与 OLED 显示提供实时反馈，可用于学习辅助、坐姿提醒和嵌入式教学实践。

## Features

- Real-time posture angle monitoring with MPU6050.
- Ambient light monitoring through ADC input.
- OLED display for posture angle, light value, alarm threshold and delay.
- Buzzer alarm when the posture angle exceeds the configured threshold for a sustained period.
- LED reminder when ambient light is below the configured threshold.
- Rotary-encoder menu for adjusting posture alarm angle and alarm delay.
- Keil MDK project structure using the STM32 standard peripheral library.

## Hardware Overview

| Module | Function |
| --- | --- |
| STM32F103C8T6 minimum system board | Main controller |
| MPU6050 | Posture angle sensing |
| 0.96 inch I2C OLED | Real-time display |
| Photoresistor module | Ambient light sensing |
| Rotary encoder | Menu and parameter adjustment |
| Active buzzer | Posture alarm output |
| LED module | Low-light reminder |
| ST-Link V2 | Programming and debugging |

For the full bill of materials, see [`docs/hardware.md`](docs/hardware.md).

## Wiring Summary

| Module | Signal | STM32 Pin |
| --- | --- | --- |
| OLED | SCL / SDA | PB8 / PB9 |
| MPU6050 | SCL / SDA | PB10 / PB11 |
| Photoresistor AO | ADC input | PA0 |
| Rotary encoder A / B / SW | Menu input | PA1 / PA2 / PA3 |
| Active buzzer IN | Alarm output | PB12 |
| LED IN | Reminder output | PB13 |
| ST-Link | SWDIO / SWCLK | PA13 / PA14 |

All modules must share a common GND. For detailed wiring and electrical notes, see [`docs/wiring.md`](docs/wiring.md).

## Quick Start

1. Install Keil MDK 5.
2. Install the STM32F1xx Device Family Pack.
3. Connect the hardware according to [`docs/wiring.md`](docs/wiring.md).
4. Open `Project/Project.uvprojx` in Keil.
5. Select `Target 1` and run `Rebuild`.
6. Download the firmware to the STM32F103C8T6 board with ST-Link.
7. Confirm that the OLED shows posture angle, light value, threshold and alarm delay.

For step-by-step build and flashing instructions, see [`docs/build.md`](docs/build.md).

## System Behavior

The system has three operating states controlled by the rotary encoder:

| State | Description |
| --- | --- |
| State 0 | Main monitoring screen. Shows angle, light value, alarm angle and delay. |
| State 1 | Posture alarm angle setting. Adjustable from 0 to 90 degrees. |
| State 2 | Alarm delay setting. Adjustable from 1 to 10 seconds. |

Default parameters in `Project/User/main.c`:

```c
#define LIGHT_ALARM_THRESHOLD   1200
#define SAMPLE_PERIOD_MS        100
static uint8_t Alarm_Angle = 25;
static uint8_t Alarm_Delay = 3;
```

## Repository Layout

```text
Project/
  Project.uvprojx              Keil MDK project file
  User/main.c                  Main program and state machine
  Hardware/                    OLED, MPU6050, ADC, encoder and I/O drivers
  Library/                     STM32F10x standard peripheral library
  Start/                       Startup files and CMSIS support
  System/                      Delay and system helper modules
  README.md                    Extended Chinese user guide

docs/
  hardware.md                  Hardware list and module notes
  wiring.md                    Wiring table and electrical notes
  build.md                     Keil build and ST-Link download guide
  troubleshooting.md           Common fault diagnosis

tools/                         Optional development scripts
```

## Documentation

- [`docs/hardware.md`](docs/hardware.md): hardware modules and bill of materials.
- [`docs/wiring.md`](docs/wiring.md): complete pin mapping and wiring cautions.
- [`docs/build.md`](docs/build.md): Keil MDK build and ST-Link download workflow.
- [`docs/troubleshooting.md`](docs/troubleshooting.md): OLED, MPU6050, ADC, encoder, buzzer, LED and download troubleshooting.
- [`Project/README.md`](Project/README.md): extended Chinese guide for beginners.

## Build Status

The latest local Keil build log is stored in `Project/build_release.log`. The current release build records `0 Error(s), 0 Warning(s)`.

## Release Plan

The first stable release is planned as `v1.0.0` and covers posture angle monitoring, ambient light monitoring, OLED display, buzzer alarm, LED reminder and rotary-encoder menu control.

See [`CHANGELOG.md`](CHANGELOG.md) for version history.

## Contributing

Issues and pull requests are welcome. Please read [`CONTRIBUTING.md`](CONTRIBUTING.md) before submitting changes.

Typical contribution areas include improving hardware compatibility, adding support for new display or sensor modules, improving calibration and filtering logic, translating documentation and reporting reproducible build or wiring issues.

## License

This project is licensed under the MIT License. See [`LICENSE`](LICENSE) for details.

## Project Origin

This repository originated from an embedded systems learning project. Course-specific files such as reports and defense slides have been removed so that the repository remains focused on the open-source embedded monitoring system.