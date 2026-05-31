# Wiring Guide

Disconnect power before wiring. All modules must share a common GND with the STM32 board.

## Pin Mapping

| Module | Module Pin | STM32 Pin | Notes |
| --- | --- | --- | --- |
| OLED | VCC | 3.3V | Recommended 3.3V power. |
| OLED | GND | GND | Common ground. |
| OLED | SCL | PB8 | OLED software I2C clock. |
| OLED | SDA | PB9 | OLED software I2C data. |
| MPU6050 | VCC | 3.3V | Recommended 3.3V power. |
| MPU6050 | GND | GND | Common ground. |
| MPU6050 | SCL | PB10 | MPU6050 software I2C clock. |
| MPU6050 | SDA | PB11 | MPU6050 software I2C data. |
| Photoresistor | VCC | 3.3V | Use analog output. |
| Photoresistor | GND | GND | Common ground. |
| Photoresistor | AO | PA0 | ADC1_IN0. |
| Rotary encoder | VCC | 3.3V | Confirm module output voltage if powered by 5V. |
| Rotary encoder | GND | GND | Common ground. |
| Rotary encoder | A | PA1 | External interrupt input. |
| Rotary encoder | B | PA2 | External interrupt input. |
| Rotary encoder | SW | PA3 | Button input, low level when pressed. |
| Active buzzer | VCC | 3.3V or 5V | Follow module specification. |
| Active buzzer | GND | GND | Common ground. |
| Active buzzer | IN | PB12 | Low-level active alarm output. |
| LED module | VCC | 3.3V | Module LED power. |
| LED module | GND | GND | Common ground. |
| LED module | IN | PB13 | Low-level active reminder output. |
| ST-Link | 3.3V | 3.3V | Reference voltage or board power, depending on setup. |
| ST-Link | GND | GND | Required. |
| ST-Link | SWDIO | SWDIO / PA13 | SWD data. |
| ST-Link | SWCLK | SWCLK / PA14 | SWD clock. |

## Important Notes

1. OLED and MPU6050 both use I2C-style connections, but this firmware assigns them to different software I2C buses.
2. OLED uses PB8/PB9. MPU6050 uses PB10/PB11. Do not swap them unless you also modify the driver code.
3. PB12 and PB13 are currently treated as low-level active outputs.
4. PA0 is an ADC input. Do not apply more than 3.3V to PA0.
5. If using a bare LED instead of an LED module, add a current-limiting resistor, typically 220 ohm to 1 kOhm.
6. If the board becomes hot, smells abnormal, or shows unstable power behavior, disconnect power immediately.

## Suggested First Power-On Sequence

To reduce debugging difficulty, connect and test modules step by step:

1. Connect only STM32, ST-Link and OLED. Download the firmware and confirm OLED output.
2. Add MPU6050 and confirm that the angle value changes when the module moves.
3. Add the photoresistor module and confirm that the light value changes when the sensor is covered or illuminated.
4. Add the rotary encoder and confirm menu switching and parameter adjustment.
5. Add the buzzer and LED and confirm alarm output behavior.