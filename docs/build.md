# Build and Flashing Guide

This guide explains how to build the firmware with Keil MDK 5 and download it to an STM32F103C8T6 board through ST-Link.

## Requirements

- Keil MDK 5.
- STM32F1xx Device Family Pack.
- ST-Link driver.
- ST-Link V2 programmer or compatible debugger.
- The complete `Project/` directory from this repository.

## Install STM32F1 Device Pack

If Keil cannot find the STM32F103C8 device, install the device pack:

1. Open Keil uVision5.
2. Open `Pack Installer`.
3. Search for `STM32F1xx`.
4. Install `Keil::STM32F1xx_DFP`.
5. Restart Keil.

## Open the Project

Open the project file:

```text
Project/Project.uvprojx
```

In the Keil project tree, confirm that these groups are visible:

```text
User
Hardware
System
Library
Start
```

## Build

1. Select `Target 1`.
2. Click `Rebuild`.
3. Confirm that the output window reports no errors.

Expected successful output:

```text
0 Error(s), 0 Warning(s)
```

Warnings may not always prevent execution, but errors must be fixed before flashing.

## Connect ST-Link

Minimum SWD wiring:

| ST-Link | STM32 |
| --- | --- |
| SWDIO | SWDIO / PA13 |
| SWCLK | SWCLK / PA14 |
| GND | GND |
| 3.3V | 3.3V |

If the STM32 board is already powered separately, the ST-Link 3.3V pin may be used only as reference voltage depending on the board and programmer. Avoid conflicting power sources.

## Configure Keil Debugger

1. Click `Options for Target`.
2. Open the `Debug` tab.
3. Select `ST-Link Debugger`.
4. Click `Settings`.
5. Set `Port` to `SW`, not JTAG.
6. Confirm that Keil can detect the target device.

## Configure Flash Download

1. In `Options for Target`, open the `Utilities` tab.
2. Enable `Use Target Driver for Flash Programming`.
3. Select `ST-Link Debugger`.
4. Open `Settings` and confirm that the correct STM32F10x flash algorithm exists.

## Download Firmware

Click the `Download` button in Keil. A successful operation should show output similar to:

```text
Flash Download finished
```

After reset, the OLED should display the monitoring screen.

## Runtime Check

After flashing:

1. Confirm that the OLED is powered and displays text.
2. Tilt the MPU6050 and confirm that the angle changes.
3. Cover or illuminate the photoresistor and confirm that the light value changes.
4. Press the encoder switch to enter the setting menu.
5. Rotate the encoder to adjust the alarm angle and delay.

If the device does not work as expected, see [`troubleshooting.md`](troubleshooting.md).