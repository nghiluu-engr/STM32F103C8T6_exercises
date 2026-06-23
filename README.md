# STM32F103C8T6_exercises

## 📌 Overview
This repository stores my exercises using the **STM32F103C8T6** (Blue Pill) microcontroller. 
All exercises are made using 2 software tools:
* **STM32CubeMX**: For setting up pins and peripheral hardware.
* **Keil uVision (Keil C)**: For writing code and uploading it to the board.

---

## 🚀 LED_PROJECT

### 1. Hardware
* **Microcontroller:** STM32F103C8T6 (Blue Pill) board.
* **Programmer:** ST-Link V2.
* **Peripherals:**
  * 4x RGB LEDs (1 common anode, 3 common cathode).
  * 1x 4-pin SMD push button (size 6x6mm).
  * Transistors (NPN, PNP), resistors, and jumper wires.

### 2. Main Code Architecture
All the main code files are placed inside the `User_Libs` folder. It includes 3 libraries:
* **Button library (`button.h` / `button.c`):** Manages the button state (checks if the button is pressed).
* **RGB LED library (`led_rgb.h` / `led_rgb.c`):** Controls each RGB LED individually.
* **LED Effect library (`led_effect.h` / `led_effect.c`):** Controls the effects of all 4 RGB LEDs together at the same time.

### 3. Programming Techniques Used
* **Non-blocking delay:** Using `HAL_GetTick()` instead of `HAL_Delay()` so the CPU can do multiple things at once without waiting.
* **Finite State Machine (FSM):** Using a state machine to switch smoothly between different LED modes when pressing the button.

### 4. LED Effects Table
When you press the button, the system switches between these modes:

| Mode | State Name | Effect Description |
| :---: | :--- | :--- |
| **0** | `STATE_OFF` | All LEDs are turned OFF. |
| **1** | `STATE_FADE_IN_OUT` | LED1 turns Red -> LED2 turns Green -> LED3 turns Blue -> LED4 turns White. After that, they turn off in reverse order from LED4 back to LED1. |
| **2** | `STATE_RAINBOW_BLINK` | All 4 RGB LEDs blink together with 7 rainbow colors. |
| **3** | `STATE_RAINBOW_FOLLOW` | Rainbow effect running one after another from LED1 -> LED2 -> LED3 -> LED4. |
