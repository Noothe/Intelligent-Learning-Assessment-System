# Contributing Guide

Thank you for considering a contribution to Intelligent Learning Assessment System.

This project welcomes practical improvements to embedded firmware, hardware compatibility and documentation. Please keep changes reproducible and easy to test on STM32F103C8T6-based boards.

## Ways to Contribute

- Report hardware wiring, build or flashing problems.
- Improve documentation, diagrams or troubleshooting notes.
- Add support for compatible sensors, displays or boards.
- Improve posture angle calibration, sampling stability or alarm logic.
- Refactor firmware while preserving the current Keil MDK build flow.

## Before Opening an Issue

Please include:

1. Your STM32 board model.
2. Keil MDK version.
3. ST-Link model or programmer type.
4. Hardware module model, especially OLED and MPU6050 variants.
5. A clear description of the fault.
6. Reproduction steps and, if possible, photos of the wiring.

## Pull Request Workflow

1. Fork the repository.
2. Create a feature branch from the default branch.
3. Make a focused change.
4. Rebuild the Keil project when firmware files are changed.
5. Update documentation when wiring, parameters or behavior changes.
6. Open a pull request with a clear summary and test notes.

## Coding Guidelines

- Keep the project compatible with Keil MDK 5 and the STM32 standard peripheral library.
- Avoid introducing unnecessary dependencies.
- Keep pin mappings documented when changing GPIO assignments.
- Use readable names for hardware abstraction functions.
- Prefer small, reviewable commits.

## Documentation Guidelines

Documentation should be useful for beginners. When adding instructions, include exact file paths, pin names and expected outputs where possible.

## License

By contributing, you agree that your contribution will be licensed under the project license unless a file clearly states otherwise.