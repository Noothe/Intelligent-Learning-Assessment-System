# 智能坐姿与学习环境监测系统使用说明

本项目基于 STM32F103C8T6、STM32 标准库和 Keil MDK 开发，实现坐姿前倾角度监测、环境光照监测、蜂鸣器报警、LED 提醒，以及旋转编码器菜单设置。

即使你没有嵌入式基础，也可以按本文一步一步完成接线、编译、下载和测试。

## 1. 你需要准备的东西

### 硬件

1. STM32F103C8T6 最小系统板，也叫 Blue Pill。
2. ST-Link V2 下载器。
3. 0.96 寸 OLED 显示屏，I2C 接口，常见引脚为 `GND VCC SCL SDA`。
4. MPU6050 陀螺仪加速度计模块，I2C 接口。
5. 光敏电阻模块，模拟输出 AO。
6. 360 度旋转编码器模块，带 A/B/SW 三个信号。
7. 有源蜂鸣器模块，低电平触发。
8. LED 模块，低电平点亮；如果没有 LED 模块，也可用普通 LED 加限流电阻。
9. 杜邦线若干。
10. 5V 或 USB 供电线。

### 软件

1. Keil MDK 5。
2. STM32F1xx Device Family Pack。
3. ST-Link 驱动。
4. 本项目文件夹：`Project`。

## 2. 引脚连接表

接线时一定要先断电。所有模块的 `GND` 必须和 STM32 的 `GND` 接在一起，否则信号没有共同参考点，程序可能完全不工作。

| 模块 | 模块引脚 | STM32 引脚 | 说明 |
| --- | --- | --- | --- |
| OLED | VCC | 3.3V | 建议使用 3.3V |
| OLED | GND | GND | 共地 |
| OLED | SCL | PB8 | OLED 软件 I2C 时钟 |
| OLED | SDA | PB9 | OLED 软件 I2C 数据 |
| MPU6050 | VCC | 3.3V | 建议使用 3.3V |
| MPU6050 | GND | GND | 共地 |
| MPU6050 | SCL | PB10 | MPU6050 软件 I2C 时钟 |
| MPU6050 | SDA | PB11 | MPU6050 软件 I2C 数据 |
| 光敏模块 | VCC | 3.3V | 使用模拟输出 AO |
| 光敏模块 | GND | GND | 共地 |
| 光敏模块 | AO | PA0 | ADC1_IN0 |
| 旋转编码器 | VCC | 3.3V | 如果模块要求 5V，请确认输出电平是否兼容 3.3V |
| 旋转编码器 | GND | GND | 共地 |
| 旋转编码器 | A | PA1 | 外部中断输入 |
| 旋转编码器 | B | PA2 | 外部中断输入 |
| 旋转编码器 | SW | PA3 | 按键输入，低电平按下 |
| 有源蜂鸣器 | VCC | 3.3V 或 5V | 按模块规格选择 |
| 有源蜂鸣器 | GND | GND | 共地 |
| 有源蜂鸣器 | IN | PB12 | 低电平触发报警 |
| 警示 LED | VCC | 3.3V | 模块式 LED 通常这样接 |
| 警示 LED | GND | GND | 共地 |
| 警示 LED | IN | PB13 | 低电平点亮 |
| ST-Link | 3.3V | 3.3V | 可只作为参考电压，不一定用它供电 |
| ST-Link | GND | GND | 必须连接 |
| ST-Link | SWDIO | SWDIO | 下载调试数据；如果板子没有 SWDIO 丝印，则接 PA13 |
| ST-Link | SWCLK | SWCLK | 下载调试时钟；如果板子没有 SWCLK 丝印，则接 PA14 |

## 3. 接线注意事项

1. OLED 和 MPU6050 都是 I2C 模块，但本项目让它们使用不同引脚：OLED 用 `PB8/PB9`，MPU6050 用 `PB10/PB11`。
2. 不要把 OLED 和 MPU6050 都接到同一组 SCL/SDA，除非你同时修改底层驱动。
3. 江科大/江科协最小系统板通常直接印有 `SWDIO` 和 `SWCLK`，下载器按同名引脚连接即可；它们在芯片内部对应 PA13 和 PA14，不要接其他模块。
4. PB12 蜂鸣器和 PB13 LED 都是低电平有效：程序输出低电平时报警或点亮，输出高电平时关闭。
5. 如果使用普通 LED，而不是模块，请串联 220 欧到 1k 欧限流电阻，避免烧坏 LED 或单片机引脚。
6. 如果某个模块只能 5V 供电，要确认它输出到 STM32 的信号不是 5V。STM32F103 的普通 GPIO 大多可容忍 5V 数字输入，但 ADC 引脚 PA0 不能输入超过 3.3V 的模拟电压。

## 4. 软件工程在哪里

Keil 工程文件在：

```text
Project\Project.uvprojx
```

主程序在：

```text
Project\User\main.c
```

关键驱动文件在：

```text
Project\Hardware\OLED.c
Project\Hardware\MPU6050.c
Project\Hardware\MyI2C.c
Project\Hardware\AD.c
Project\Hardware\Encoder.c
```

## 5. 安装 Keil 和芯片包

### 5.1 安装 Keil MDK 5

安装 Keil MDK 5 后，桌面或开始菜单中应能看到 `Keil uVision5`。

### 5.2 安装 STM32F1 芯片包

打开 Keil 后，如果提示找不到 STM32F103C8 设备，说明还没有安装芯片包。

安装方法：

1. 打开 Keil。
2. 点击菜单 `Pack Installer`。
3. 搜索 `STM32F1xx`。
4. 安装 `Keil::STM32F1xx_DFP`。
5. 安装完成后重启 Keil。

## 6. 编译工程

1. 双击打开：

```text
Project\Project.uvprojx
```

2. 在 Keil 左侧工程树中确认能看到 `User`、`Hardware`、`System`、`Library`、`Start` 等分组。
3. 点击工具栏上的 `Build` 按钮，图标通常像一个锤子。
4. 编译成功时，底部输出窗口应显示类似：

```text
0 Error(s), 0 Warning(s)
```

有少量 Warning 不一定影响运行，但如果有 Error 必须先解决。

## 7. 下载到 STM32

### 7.1 连接 ST-Link

ST-Link 和 STM32 最少连接 4 根线。优先按板子丝印接 `SWDIO`、`SWCLK`；如果你的板子没有这两个丝印，再找 PA13、PA14：

| ST-Link | STM32 |
| --- | --- |
| SWDIO | SWDIO，或 PA13 |
| SWCLK | SWCLK，或 PA14 |
| GND | GND |
| 3.3V | 3.3V |

如果 STM32 已经通过 USB 单独供电，ST-Link 的 3.3V 可以只作为参考电压连接；不要让多个电源互相冲突。

### 7.2 Keil 中选择 ST-Link

1. 点击 `Options for Target`，图标通常像魔法棒。
2. 进入 `Debug` 选项卡。
3. 右侧下拉框选择 `ST-Link Debugger`。
4. 点击 `Settings`。
5. Port 选择 `SW`，不要选 JTAG。
6. 如果连接正常，窗口里会显示芯片信息。

### 7.3 设置 Flash Download

1. 仍在 `Options for Target` 中。
2. 进入 `Utilities` 选项卡。
3. 勾选 `Use Target Driver for Flash Programming`。
4. 选择 `ST-Link Debugger`。
5. 点击 `Settings`，确认 Flash 算法里有 STM32F10x 对应算法。

### 7.4 下载

点击 Keil 工具栏的 `Download` 按钮，图标通常写着 `LOAD`。

下载成功后，底部输出窗口会出现类似：

```text
Flash Download finished
```

## 8. 系统怎么使用

系统有 3 个状态，通过旋转编码器和编码器按键操作。

### 状态 0：主监控界面

OLED 显示：

1. 第 1 行显示 `Posture Monitor`。
2. 第 2 行显示当前前倾角度 `Angle`。
3. 第 3 行显示当前光照 ADC 值 `Light`。
4. 第 4 行显示当前角度报警阈值 `Set` 和报警延迟时间 `D`。

报警逻辑：

1. 当前角度大于设定角度 `Alarm_Angle`，并且持续超过 `Alarm_Delay` 秒，蜂鸣器响。
2. 光照 ADC 值低于阈值 `1200`，LED 点亮。

操作：

1. 按下编码器按键，进入角度阈值设置界面。

### 状态 1：角度阈值设置

OLED 显示当前报警角度阈值。

操作：

1. 旋转编码器，调节报警角度。
2. 范围为 `0` 到 `90` 度。
3. 按下编码器按键，进入报警延迟设置界面。

### 状态 2：报警延迟设置

OLED 显示当前报警延迟时间。

操作：

1. 旋转编码器，调节报警延迟。
2. 范围为 `1` 到 `10` 秒。
3. 按下编码器按键，返回主监控界面。

## 9. 程序里的默认参数

在 `User\main.c` 中可以看到这些参数：

```c
#define LIGHT_ALARM_THRESHOLD   1200
#define SAMPLE_PERIOD_MS        100
static uint8_t Alarm_Angle = 25;
static uint8_t Alarm_Delay = 3;
```

含义：

1. `LIGHT_ALARM_THRESHOLD`：光照报警阈值。ADC 值低于它时 LED 点亮。
2. `SAMPLE_PERIOD_MS`：主循环采样周期，当前为 100 ms。
3. `Alarm_Angle`：默认坐姿角度报警阈值，当前为 25 度。
4. `Alarm_Delay`：默认持续超限多久后蜂鸣器报警，当前为 3 秒。

## 10. MPU6050 安装方向

程序当前用 MPU6050 的 `AccX` 轴计算前倾角度。

如果你发现身体前倾时 OLED 上角度几乎不变，说明模块安装方向和程序假设不一致。

解决方法：

1. 打开 `User\main.c`。
2. 找到函数 `Calculate_PostureAngle()`。
3. 当前代码类似：

```c
x = (float)ax;
```

4. 如果前倾对应 Y 轴，改成：

```c
x = (float)ay;
```

5. 如果角度方向反了，通常不用处理，因为程序使用的是绝对倾斜量。

## 11. 常见问题排查

### 11.1 OLED 不亮

可能原因：

1. VCC/GND 接反或没接。
2. SCL/SDA 接反。
3. OLED 接到了 PB10/PB11，而程序使用 PB8/PB9。
4. OLED 模块地址不是常见的 `0x78` 或 `0x7A`。
5. 供电不足。

处理方法：

1. 确认 OLED：`SCL -> PB8`，`SDA -> PB9`。
2. 确认 GND 共地。
3. 换一根杜邦线测试。
4. 本项目的 `Hardware\OLED.c` 已兼容常见 `0x78` 和 `0x7A` 两种地址；如果仍不显示，再用 I2C 扫描或查模块资料确认地址。

### 11.2 OLED 有显示，但 MPU6050 数据不正常

可能原因：

1. MPU6050 的 SCL/SDA 接错。
2. MPU6050 没有供电。
3. MPU6050 接到了 PB8/PB9，而程序使用 PB10/PB11。
4. 模块损坏或焊接不良。

处理方法：

1. 确认 MPU6050：`SCL -> PB10`，`SDA -> PB11`。
2. 确认 VCC 接 3.3V，GND 共地。
3. 摇动模块，看角度是否变化。

### 11.3 光照数值一直是 0 或 4095

可能原因：

1. 光敏模块 AO 没有接到 PA0。
2. 接成了 DO 数字输出，而不是 AO 模拟输出。
3. 模块电位器调节过头。
4. 供电或 GND 异常。

处理方法：

1. 确认使用 `AO -> PA0`。
2. 用手遮挡光敏电阻，看 OLED 上 Light 是否变化。
3. 调节模块上的小电位器。
4. ADC 输入不能超过 3.3V。

### 11.4 旋转编码器没有反应

可能原因：

1. A/B 相接错或没接。
2. 编码器没有接 VCC/GND。
3. 模块输出电平不稳定。
4. 编码器转得太快，机械抖动导致跳变。

处理方法：

1. 确认 `A -> PA1`，`B -> PA2`，`SW -> PA3`。
2. 如果方向反了，可以交换 A/B 线，也可以在程序中把加减方向对调。
3. 慢慢转动编码器测试。

### 11.5 按下编码器按键没有切换菜单

可能原因：

1. SW 没接到 PA3。
2. SW 按下后不是低电平。
3. GND 没有共地。

处理方法：

1. 确认 `SW -> PA3`。
2. 确认编码器模块 GND 接 STM32 GND。
3. 用万用表测量 PA3，按下时应接近 0V，松开时应接近 3.3V。

### 11.6 蜂鸣器一直响

可能原因：

1. 蜂鸣器模块不是低电平触发。
2. PB12 接线错误。
3. 姿态角度一直超过报警阈值。
4. MPU6050 安装方向不对，导致角度计算偏大。

处理方法：

1. 确认蜂鸣器 IN 接 PB12。
2. 在菜单中把报警角度调大，比如调到 60 度。
3. 把 MPU6050 平放测试。
4. 如果你的蜂鸣器是高电平触发，需要修改 `Set_Buzzer()` 函数的输出逻辑。

### 11.7 LED 一直亮

可能原因：

1. 环境光确实低于阈值。
2. 光敏模块 AO 输出方向和程序阈值假设相反。
3. LED 模块不是低电平点亮。
4. PB13 接线错误。

处理方法：

1. 用强光照射光敏模块，看 Light 数值是否变化。
2. 修改 `LIGHT_ALARM_THRESHOLD`，例如改成 500 或 2000 再试。
3. 如果 LED 是高电平点亮，需要修改 `Set_LED()` 函数的输出逻辑。

### 11.8 Keil 编译报错找不到头文件

可能原因：

1. 工程文件没有放在完整 `Project` 文件夹中。
2. Keil 的 Include Path 被误删。
3. 文件夹移动后路径异常。

处理方法：

1. 确认工程目录中有 `User`、`Hardware`、`System`、`Library`、`Start` 文件夹。
2. 在 Keil 中打开 `Options for Target -> C/C++`。
3. Include Paths 应包含：

```text
.\Start;.\Library;.\User;.\System;.\Hardware
```

### 11.9 Keil 提示找不到 STM32F103C8

原因：没有安装 STM32F1 芯片包。

处理方法：

1. 打开 Keil 的 `Pack Installer`。
2. 安装 `Keil::STM32F1xx_DFP`。
3. 重启 Keil。

### 11.10 下载失败，提示 No target connected

可能原因：

1. ST-Link 没插好。
2. SWDIO/SWCLK 接反。
3. 没有共地。
4. STM32 没供电。
5. Debug 接口选成了 JTAG。

处理方法：

1. 确认 `SWDIO -> SWDIO`，`SWCLK -> SWCLK`。如果板子没有 SWDIO/SWCLK 丝印，则确认 `SWDIO -> PA13`，`SWCLK -> PA14`。
2. 确认 ST-Link GND 和 STM32 GND 相连。
3. Keil 中 `Debug -> Settings -> Port` 选择 `SW`。
4. 按住 STM32 复位键，再点击下载，有时可以恢复连接。

### 11.11 下载后程序不运行

可能原因：

1. BOOT0 跳线位置不对。
2. 程序没有成功下载。
3. 板子供电不稳定。
4. 外设短路导致复位。

处理方法：

1. BOOT0 应接低电平，也就是正常从 Flash 启动。
2. 重新点击 Keil 的 Download。
3. 断开所有外设，只保留 OLED 测试。
4. 检查 3.3V 和 GND 是否短路。

## 12. 初次上电建议流程

建议不要一次性接上所有模块。按下面顺序更容易定位问题：

1. 只接 STM32、ST-Link、OLED，下载程序，确认 OLED 显示。
2. 接 MPU6050，确认角度会变化。
3. 接光敏模块，确认 Light 数值会变化。
4. 接旋转编码器，确认可以切换菜单和调节参数。
5. 接蜂鸣器和 LED，确认报警输出正常。

## 13. 安全提醒

1. 接线前断电。
2. 不要把 5V 接到 STM32 的 3.3V 引脚。
3. 不要把超过 3.3V 的模拟信号接到 PA0。
4. LED 必须限流。
5. 如果板子发热、冒烟、有异味，立即断电。

## 14. 项目文件说明

| 文件 | 作用 |
| --- | --- |
| `User\main.c` | 主状态机、报警逻辑、菜单逻辑 |
| `Hardware\OLED.c` | OLED 显示驱动 |
| `Hardware\MPU6050.c` | MPU6050 数据读取 |
| `Hardware\MyI2C.c` | MPU6050 软件 I2C，使用 PB10/PB11 |
| `Hardware\AD.c` | PA0 光敏 ADC 采样 |
| `Hardware\Encoder.c` | PA1/PA2 旋转编码器计数 |
| `System\Delay.c` | 延时函数 |
| `Project.uvprojx` | Keil 工程文件 |

## 15. 可以自行调整的地方

如果想调整报警灵敏度，优先修改 `User\main.c` 中的这些参数：

```c
#define LIGHT_ALARM_THRESHOLD   1200
static uint8_t Alarm_Angle = 25;
static uint8_t Alarm_Delay = 3;
```

如果只想临时调节角度和延迟，不需要改代码，直接用旋转编码器菜单设置即可。
