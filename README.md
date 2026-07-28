# STM32-Button-Controlled-Breathing-LED

> A breathing LED implementation on STM32F103 with 3-speed button control

[![STM32](https://img.shields.io/badge/STM32-F103C8-03234B?style=for-the-badge&logo=stmicroelectronics)](https://www.st.com/en/microcontrollers-microprocessors/stm32f103c8.html)
[![HAL](https://img.shields.io/badge/HAL-STM32F1-0091BD?style=for-the-badge)](https://github.com/STMicroelectronics/STM32CubeF1)
[![License](https://img.shields.io/badge/License-BSD--3--Clause-3DA639?style=for-the-badge)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-STM32-0078D4?style=for-the-badge&logo=c)](https://www.st.com)

---

## 📖 Overview

This project demonstrates a **breathing LED effect** on an STM32F103 microcontroller using **hardware PWM** from Timer 4 (TIM4). Two physical buttons allow the user to switch between **three distinct breathing speeds**, providing a simple and intuitive human-machine interaction.

> 🔥 **Why this project matters:** This is an ideal starting point for beginners to understand STM32's **PWM generation**, **timer configuration**, **GPIO input handling**, and **state management** — all fundamental building blocks for embedded systems development.

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🎛️ **3 Speed Levels** | Switch between Fast, Medium, and Slow breathing modes |
| 🔘 **Dual Button Control** | KEY1 = Increase speed, KEY2 = Decrease speed |
| 💡 **Two PWM Channels** | TIM4 CH3 (PB8) and CH4 (PB9) drive two LEDs simultaneously |
| ⏱️ **Accurate PWM** | 16-bit timer with 100Hz base frequency, 500-step resolution |
| 🔄 **Real-time Adjustment** | Speed changes take effect immediately without reset |
| 📦 **Modular Code** | Clean separation of GPIO, TIM, and KEY modules |

---

## 🧩 System Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                     STM32F103C8T6                          │
│                                                             │
│   ┌──────────┐     ┌──────────┐     ┌──────────────────┐  │
│   │   KEY1   │────▶│          │     │   TIM4_CH3 (PB8) │──┼──▶ LED1
│   │  (PB0)   │     │  Button  │     │                  │  │
│   └──────────┘     │  Handler │     └──────────────────┘  │
│   ┌──────────┐     │          │     ┌──────────────────┐  │
│   │   KEY2   │────▶│  (key.c) │     │   TIM4_CH4 (PB9) │──┼──▶ LED2
│   │  (PB1)   │     └──────────┘     └──────────────────┘  │
│   └──────────┘           │                                │
│                          ▼                                │
│                  ┌──────────────────┐                     │
│                  │  PWM Generator   │                     │
│                  │   (tim.c)        │                     │
│                  └──────────────────┘                     │
│                          │                                │
│                          ▼                                │
│                  ┌──────────────────┐                     │
│                  │  Breathing Core  │                     │
│                  │   (main.c)       │                     │
│                  └──────────────────┘                     │
└─────────────────────────────────────────────────────────────┘
```

---

## 🔌 Hardware Connection

| Component | Pin | Description |
|-----------|-----|-------------|
| **LED1** | PB8 | TIM4_CH3 - PWM output for LED 1 |
| **LED2** | PB9 | TIM4_CH4 - PWM output for LED 2 |
| **KEY1** | PB0 | Pull-up input, active low (press = 0) |
| **KEY2** | PB1 | Pull-up input, active low (press = 0) |
| **LED Indicator** | PA1 | Debug/status LED (optional) |

> ⚠️ **Note:** Both KEY1 and KEY2 have internal pull-up resistors enabled. A button press pulls the pin to GND (active low).

---

## 🎮 Operating Instructions

| Action | Effect |
|--------|--------|
| **Press KEY1** | Increase breathing speed (1 → 2 → 3) |
| **Press KEY2** | Decrease breathing speed (3 → 2 → 1) |
| **Hold KEY1 or KEY2** | Single press detection (no repeat) — prevents accidental switching |

### Speed Level Details

| Level | PWM Step Increment | Delay Between Steps | Visual Effect |
|-------|-------------------|---------------------|---------------|
| **1 (Fast)** | 1 | 1 ms | Rapid, lively breathing |
| **2 (Medium)** | 1 | 15 ms | Natural, calm breathing |
| **3 (Slow)** | 1 | 100 ms | Gentle, deep breathing |

---

## 🛠️ Technical Specifications

| Parameter | Value |
|-----------|-------|
| **MCU** | STM32F103C8T6 (ARM Cortex-M3 @ 72 MHz) |
| **Timer** | TIM4 (16-bit, up-counter) |
| **PWM Frequency** | 100 Hz (Period = 500, Prescaler = 71) |
| **PWM Resolution** | 500 steps (0 ~ 499) |
| **PWM Channels** | CH3 (PB8), CH4 (PB9) |
| **PWM Polarity** | Active Low (TIM_OCPOLARITY_LOW) |
| **Button Debounce** | 30 ms software debounce |
| **System Clock** | 72 MHz (HSE 8MHz × 9 PLL) |

---

## 📂 Project Structure

```
STM32-Button-Controlled-Breathing-LED/
├── Core/
│   ├── Inc/
│   │   ├── main.h          # Main header, pin definitions
│   │   ├── gpio.h          # GPIO prototypes
│   │   ├── tim.h           # TIM prototypes
│   │   ├── key.h           # KEY module prototypes
│   │   └── stm32f1xx_it.h  # Interrupt handlers
│   └── Src/
│       ├── main.c          # Main logic & breathing engine
│       ├── gpio.c          # GPIO initialization
│       ├── tim.c           # TIM4 PWM configuration
│       ├── key.c           # Button reading with debounce
│       ├── stm32f1xx_it.c  # Interrupt service routines
│       └── system_stm32f1xx.c
├── .ioc                    # STM32CubeMX configuration
└── README.md               # This file
```

---

## 🚀 Getting Started

### Prerequisites

| Tool | Version | Purpose |
|------|---------|---------|
| **STM32CubeMX** | v6.8+ | Project initialization and pin configuration |
| **STM32CubeIDE** | v1.12+ | Development, build, and debug |
| **STM32CubeF1** | v1.8+ | HAL driver library for STM32F1 series |
| **Debugger** | ST-Link V2 | Programming and debugging (onboard or external) |

### Build & Flash

1. Open the `.ioc` file with **STM32CubeMX** to regenerate code (if needed)
2. Import the project into **STM32CubeIDE**
3. Build the project: `Project → Build All` (or `Ctrl + B`)
4. Connect your ST-Link debugger
5. Flash: `Run → Debug` (or `F11`)
6. Press the reset button to start execution

---

## 🧠 Key Concepts Illustrated

### PWM Breathing Algorithm

The breathing effect is achieved by **linearly increasing and decreasing** the PWM compare value (CCR), which controls the LED brightness. The `flag` variable determines whether the value is ramping up or down:

```c
if (flag == 0) i++;  // Ramp up (brightness increases)
else i--;            // Ramp down (brightness decreases)

if (i >= 400) flag = 1;  // Reached peak → start dimming
if (i <= 0) flag = 0;    // Reached bottom → start brightening

htim4.Instance->CCR3 = i;  // Apply to CH3
htim4.Instance->CCR4 = i;  // Apply to CH4
```

### Button Debouncing

A **30ms software delay** is used to eliminate mechanical contact bounce:

```c
if ((!KEY1 || !KEY2) && !stat) {
    stat = 1;           // Lock to prevent repeated trigger
    HAL_Delay(30);      // Debounce delay
    // Validate and return key value
}
```

---

## 🎯 Learning Outcomes

By studying this project, you will understand:

- ✅ How to configure **TIMER PWM output** using STM32CubeMX
- ✅ How to control **LED brightness** with pulse-width modulation
- ✅ How to implement **button debouncing** in software
- ✅ How to design a **finite state machine** for mode switching
- ✅ How to structure a **modular embedded C project**
- ✅ How to use **HAL libraries** for peripheral control

---
