# Troubleshooting Guide

This guide lists common hardware, firmware and flashing problems.

## OLED Does Not Light Up

Possible causes:

1. VCC and GND are not connected correctly.
2. SCL and SDA are swapped.
3. OLED is connected to PB10/PB11 while the firmware uses PB8/PB9.
4. OLED I2C address is not compatible with the current driver.
5. Power supply is unstable.

Recommended checks:

1. Confirm `SCL -> PB8` and `SDA -> PB9`.
2. Confirm common GND.
3. Replace Dupont wires and test again.
4. Check whether the OLED module uses a common I2C address supported by the driver.

## OLED Works but MPU6050 Data Is Abnormal

Possible causes:

1. MPU6050 SCL/SDA wiring is incorrect.
2. MPU6050 has no power.
3. MPU6050 is connected to PB8/PB9 while the firmware uses PB10/PB11.
4. Module soldering or module quality is faulty.

Recommended checks:

1. Confirm `SCL -> PB10` and `SDA -> PB11`.
2. Confirm VCC and GND.
3. Move or tilt the MPU6050 and check whether the angle changes.

## Light Value Is Always 0 or 4095

Possible causes:

1. The photoresistor AO pin is not connected to PA0.
2. The digital output pin DO is connected instead of AO.
3. The module potentiometer is adjusted to an extreme value.
4. PA0 receives an invalid voltage level.

Recommended checks:

1. Confirm `AO -> PA0`.
2. Cover and illuminate the photoresistor to see whether the value changes.
3. Adjust the module potentiometer.
4. Ensure that PA0 input voltage does not exceed 3.3V.

## Rotary Encoder Does Not Respond

Possible causes:

1. A/B phase pins are not connected correctly.
2. Encoder VCC/GND is missing.
3. Module output is unstable.
4. The encoder is rotated too quickly during testing.

Recommended checks:

1. Confirm `A -> PA1`, `B -> PA2`, and `SW -> PA3`.
2. Rotate the encoder slowly.
3. If the direction is reversed, swap A/B wiring or modify the direction logic in firmware.

## Encoder Button Does Not Switch Menu

Possible causes:

1. SW is not connected to PA3.
2. SW does not produce a low level when pressed.
3. GND is not shared.

Recommended checks:

1. Confirm `SW -> PA3`.
2. Measure PA3 with a multimeter. It should be near 0V when pressed and near 3.3V when released.

## Buzzer Keeps Beeping

Possible causes:

1. The buzzer module is not low-level active.
2. PB12 wiring is incorrect.
3. The posture angle is continuously above the alarm threshold.
4. The MPU6050 mounting direction does not match the firmware assumption.

Recommended checks:

1. Confirm `IN -> PB12`.
2. Increase the alarm angle in the menu, for example to 60 degrees.
3. Place the MPU6050 flat and test again.
4. If the buzzer is high-level active, modify the output logic in `Set_Buzzer()`.

## LED Keeps Lighting

Possible causes:

1. Ambient light is actually below the threshold.
2. The photoresistor module output direction differs from the firmware assumption.
3. The LED module is not low-level active.
4. PB13 wiring is incorrect.

Recommended checks:

1. Illuminate the photoresistor with strong light and observe the displayed light value.
2. Modify `LIGHT_ALARM_THRESHOLD`, for example to 500 or 2000.
3. If the LED is high-level active, modify the output logic in `Set_LED()`.

## Keil Cannot Find Header Files

Possible causes:

1. The project is not opened from the complete `Project/` folder.
2. Keil include paths have been removed or changed.
3. Files were moved after the project was created.

Expected include paths:

```text
.\Start;.\Library;.\User;.\System;.\Hardware
```

## Keil Cannot Find STM32F103C8

Cause: the STM32F1 device family pack is not installed.

Fix:

1. Open Keil `Pack Installer`.
2. Install `Keil::STM32F1xx_DFP`.
3. Restart Keil.

## Download Fails with No Target Connected

Possible causes:

1. ST-Link is not connected correctly.
2. SWDIO and SWCLK are swapped.
3. GND is not shared.
4. STM32 has no power.
5. Keil debug port is set to JTAG instead of SW.

Recommended checks:

1. Confirm `SWDIO -> PA13` and `SWCLK -> PA14` when the board has no SWDIO/SWCLK labels.
2. Confirm ST-Link GND and STM32 GND are connected.
3. Set `Debug -> Settings -> Port` to `SW`.
4. Hold the reset button while starting download if the chip cannot be detected.

## Firmware Downloads but Does Not Run

Possible causes:

1. BOOT0 jumper is in the wrong position.
2. Firmware download did not complete successfully.
3. Power supply is unstable.
4. Peripheral wiring causes a short circuit or reset.

Recommended checks:

1. Set BOOT0 to low level so the chip boots from Flash.
2. Download again from Keil.
3. Disconnect all peripherals except OLED and test the minimum setup.
4. Check whether 3.3V and GND are shorted.