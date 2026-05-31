# Changelog

All notable changes to this project will be documented in this file.

This project uses simple semantic versioning: `MAJOR.MINOR.PATCH`.

## [Unreleased]

### Added

- Open-source project README structure.
- Contributing guide.
- Split documentation for hardware, wiring, build and troubleshooting.

### Changed

- Repositioned the repository as an open-source embedded posture and learning-environment monitoring system.
- Removed course-specific report and defense presentation files from the public project entry point.

## [1.0.0] - Planned

### Added

- STM32F103C8T6 firmware project for Keil MDK.
- MPU6050-based posture angle monitoring.
- Photoresistor-based ambient light monitoring through ADC.
- OLED display for monitoring values and configuration.
- Buzzer alarm for sustained posture threshold exceedance.
- LED reminder for low-light condition.
- Rotary-encoder menu for alarm angle and delay configuration.

### Build

- Keil MDK project structure based on STM32 standard peripheral library.
- Local build target records `0 Error(s), 0 Warning(s)` in `Project/build_release.log`.