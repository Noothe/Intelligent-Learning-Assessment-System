# 智能坐姿与学习环境监测系统

本仓库为电子系统设计课程设计项目，基于 STM32F103C8T6、STM32 标准外设库与 Keil MDK 开发，实现坐姿前倾角度监测、环境光照监测、蜂鸣器报警、LED 提醒和旋转编码器菜单设置等功能。

## 项目结构

```text
Project/
  Project.uvprojx              Keil MDK 工程文件
  User/main.c                  主程序入口
  Hardware/                    OLED、MPU6050、ADC、编码器等模块驱动
  Library/                     STM32F10x 标准外设库
  Start/                       启动文件与 CMSIS 支持文件
  System/                      延时等系统辅助模块
  README.md                    详细接线、编译和测试说明
  20231492213 宋佳骏.docx      课程设计论文
  论文插图/                    论文配图
tools/
  build_course_paper.py        论文生成辅助脚本
答辩ppt.pptx                   答辩演示文稿
```

## 快速使用

1. 安装 Keil MDK 5 和 STM32F1xx Device Family Pack。
2. 使用 Keil 打开 `Project/Project.uvprojx`。
3. 选择 `Target 1` 后执行 Rebuild。
4. 通过 ST-Link 将生成的程序下载到 STM32F103C8T6 开发板。

详细硬件接线、模块说明、阈值设置和测试步骤见 [Project/README.md](Project/README.md)。

## 硬件模块

- STM32F103C8T6 最小系统板
- 0.96 寸 I2C OLED 显示屏
- MPU6050 姿态传感器
- 光敏电阻模块
- 旋转编码器模块
- 有源蜂鸣器模块
- LED 提醒模块
- ST-Link 下载器

## 编译结果

最近一次 Keil 构建记录见 `Project/build_release.log`。该记录显示工程可完成 Rebuild，结果为 `0 Error(s), 0 Warning(s)`。

## 仓库说明

本仓库只保留课程设计核心工程、文档和必要辅助脚本。课程资料、参考手册、工具安装包、Keil 编译输出和临时生成文件未纳入版本管理。
