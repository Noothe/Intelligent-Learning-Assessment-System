# Package Manifest

Version: `1.0.0`

This package is the first stable source package for Intelligent Learning Assessment System.

## Package Contents

```text
Project/                       Keil MDK firmware project
Project/Project.uvprojx        Keil project file
Project/User/main.c            Main application, state machine and alarm logic
Project/Hardware/              OLED, MPU6050, ADC, encoder and I/O drivers
Project/Library/               STM32F10x standard peripheral library
Project/Start/                 Startup files and CMSIS support
Project/System/                Delay and system helper modules
Project/README.md              Extended Chinese setup and operation guide

docs/hardware.md               Hardware guide
docs/wiring.md                 Wiring guide
docs/build.md                  Build and ST-Link flashing guide
docs/troubleshooting.md        Troubleshooting guide

README.md                      Project overview
CONTRIBUTING.md                Contribution guide
CHANGELOG.md                   Version history
LICENSE                        MIT License
VERSION                        Current package version
```

## Included Features

- STM32F103C8T6 firmware project for Keil MDK.
- MPU6050-based posture angle monitoring.
- Photoresistor-based ambient light monitoring through ADC.
- OLED display for posture angle, light value, alarm threshold and delay.
- Buzzer alarm for sustained posture threshold exceedance.
- LED reminder for low-light conditions.
- Rotary-encoder menu for alarm angle and delay configuration.

## Excluded Files

Course-specific report files, defense presentation files and report-generation helper scripts are intentionally excluded from this package.

## Build Requirements

- Keil MDK 5.
- STM32F1xx Device Family Pack.
- ST-Link driver.
- ST-Link V2 or compatible programmer.

## Build Verification

The current local Keil build status recorded in `Project/build_release.log` is:

```text
0 Error(s), 0 Warning(s)
```

## Recommended GitHub Release Asset Name

If you upload a release asset manually, use:

```text
Intelligent-Learning-Assessment-System-v1.0.0-source.zip
```

GitHub will also automatically provide source code archives for the `v1.0.0` tag after a release is published.