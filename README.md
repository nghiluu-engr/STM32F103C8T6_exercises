# STM32F103C8T6_exercises

## Overview
This repository stores my exercises using the **STM32F103C8T6** (Blue Pill) microcontroller. 
All exercises are written in the **C language** and are made using 2 software tools:
* **STM32CubeMX**: For setting up pins and peripheral hardware.
* **Keil uVision (Keil C)**: For writing code and uploading it to the board.

---

## LED_PROJECT

### 1. Hardware
* **Microcontroller:** STM32F103C8T6 (Blue Pill) board.
* **Programmer:** ST-Link V2.
* **Peripherals:**
  * 4x RGB LEDs (1 common anode, 3 common cathode).
  * 1x 4-pin SMD push button (size 6x6mm).
  * Transistors (NPN, PNP), resistors, and jumper wires.

### 2. Main Code 
All the main code files are placed inside the `User_Libs` folder. It includes 3 libraries:
* **Button library (`button.h` / `button.c`):** Manages the button state (checks if the button is pressed).
* **RGB LED library (`led_rgb.h` / `led_rgb.c`):** Controls each RGB LED individually.
* **LED Effect library (`led_effect.h` / `led_effect.c`):** Controls the effects of all 4 RGB LEDs together at the same time.

### 3. Programming Techniques Used
* **Non-blocking delay:** Using `HAL_GetTick()` instead of `HAL_Delay()` so the CPU can do multiple things at once without waiting.
* **Finite State Machine (FSM):** Using a state machine to switch smoothly between different LED modes when pressing the button.

### 4. Requirements
When you press the button, the system switches between these modes:

| Mode | State Name | Effect Description |
| :---: | :--- | :--- |
| **0** | `STATE_OFF` | All LEDs are turned OFF. |
| **1** | `STATE_FADE_IN_OUT` | LED1 turns Red -> LED2 turns Green -> LED3 turns Blue -> LED4 turns White. After that, they turn off in reverse order from LED4 back to LED1. |
| **2** | `STATE_RAINBOW_BLINK` | All 4 RGB LEDs blink together with 7 rainbow colors. |
| **3** | `STATE_RAINBOW_FOLLOW` | Rainbow effect running one after another from LED1 -> LED2 -> LED3 -> LED4. |

---

## SPI_DESIGN

### 1. Hardware
* **Microcontroller:** 2x STM32F103C8T6 (Blue Pill) boards (One acts as Master, one acts as Slave).
* **Programmer:** ST-Link V2.
* **Peripherals:** * 1x DIP LED.
  * Jumper wires to connect the SPI pins between the two boards (MOSI, MISO, SCK, NSS, and GND).

### 2. Main Code
The main code files are separated into two different project folders: `SPI_MASTER` and `SPI_SLAVE`. Each folder has its own custom library:
* **Master library (inside `SPI_MASTER` folder):** Configures the first Blue Pill board to be the SPI Master. It controls the clock and starts the communication.
* **Slave library (inside `SPI_SLAVE` folder):** Configures the second Blue Pill board to be the SPI Slave. It waits for commands and data from the Master.

### 3. Requirements
* **SPI Communication:** Using the Serial Peripheral Interface (SPI) protocol with the STM32 HAL library.
* **Data Exchange & LED Control:** * The Master board sends a specific data command to the Slave board.
  * When the Slave board receives this data, it turns on the DIP LED.
  * The Slave board sends the number `1000` back to the Master board.
 
 
---

## SRF05_ULTRASONIC_PROJECT

### 1. Hardware
* **Microcontroller:** STM32F103C8T6 (Blue Pill) board.
* **Programmer:** ST-Link V2.
* **Peripherals:** * 1x Ultrasonic Sensor (SRF05 / SRF04).
  * Jumper wires to connect the sensor (VCC, GND, Trig, and Echo) to the board.

### 2. Main Code
All the main code files are placed inside the `User_Libs` folder:
* **Ultrasonic Library (`srf05.h` / `srf05.c`):** Manages the SRF05/SRF04 sensor. It triggers the sensor to send sound waves and processes the incoming Echo signal on the microcontroller.

### 3. Techniques
* **External Interrupt (GPIO EXTI):** Configured to detect both the rising edge (when Echo pin goes HIGH) and falling edge (when Echo pin goes LOW) of the Echo signal.
* **Timer Counter:** Used to measure exactly how long the Echo pin stays HIGH.
* **Finite State Machine (FSM):** Uses a simple state machine to manage different steps of the sensor reading process (e.g., Sending Trigger -> Waiting for Echo -> Measuring Time -> Calculating Distance).

### 4. Requirements
* **Distance Calculation:** Calculate the exact distance from the sensor to an object based on the response time of the ultrasonic sound wave.
