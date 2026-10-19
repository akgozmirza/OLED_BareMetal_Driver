# OLED_BareMetal_Driver
Lightweight, dependency-free C/C++ bare-metal driver for SSD1306/SSD1315 OLED displays on embedded microcontrollers.
# ATmega328P Bare-Metal SSD1306 OLED Driver (I2C / TWI)

This repository contains a **zero-dependency, register-level I2C (TWI) driver** and custom font rendering engine for the **SSD1306 OLED Display (128x64)**, developed for the **ATmega328P** (Arduino Uno) microcontroller.

---

## Engineering & Technical Motivation
The primary goal of this project is to eliminate high-level abstractions (such as `Wire.h` or `Adafruit_SSD1306`) and build an OLED display driver from scratch by directly analyzing the ATmega328P and SSD1306 datasheets. 

Key technical focus areas:
- **Hardware Register Manipulation:** Direct control over TWI hardware registers (`TWBR`, `TWSR`, `TWCR`, `TWDR`).
- **I2C Protocol Mechanics:** Handshaking, START/STOP conditions, bit-rate generation (100 kHz SCL), and ACK/NACK verification.
- **Display Controller Initialization:** Powering up the internal charge pump (`0x8D`, `0x14`) and configuring memory addressing modes without third-party frameworks.
- **Custom Font Engine:** Dynamic rendering of characters using vertical bit-map data (5x7 column bytes) sent to the GDDRAM.

---

## Hardware & Setup
- **Microcontroller:** ATmega328P (Arduino Uno / Bare AVR)
- **Display:** 0.96" SSD1306 I2C OLED Display (128x64)
- **Protocol:** I2C (Two-Wire Interface) @ 100 kHz
- **Connection:**
  - `SDA` $\rightarrow$ ATmega328P Pin `A4` (PC4)
  - `SCL` $\rightarrow$ ATmega328P Pin `A5` (PC5)
  - `VCC` $\rightarrow$ 3.3V / 5V
  - `GND` $\rightarrow$ GND

---

## Software Architecture

### 1. Register-Level TWI / I2C Layer
Communication is handled by writing directly to the AVR TWI hardware registers:
- `TWBR = 72;` sets the SCL clock frequency to 100 kHz (assuming 16 MHz CPU clock).
- Handshaking states are polled via `while(!(TWCR & (1 << TWINT)));`.

### 2. Control Byte Logic
SSD1306 distinguishes incoming data using a **Control Byte**:
- `0x00` $\rightarrow$ Command Mode ($D/C\# = 0$)
- `0x40` $\rightarrow$ Data Mode ($D/C\# = 1$)

### 3. Font & Text Rendering
- **GDDRAM Structure:** SSD1306 uses vertical page addressing where 1 data byte represents an 8-pixel vertical column.
- **Font Matrix:** Standard $5 \times 7$ bit arrays map character columns directly to memory.
- **String Rendering:** `oled_print()` sequentially streams character byte arrays and automatically increments column positions.

---

## How to Build and Run

### Option A: Using PlatformIO (VS Code)
1. Clone this repository:
   ```bash
   git clone [https://github.com/akgozmirza/OLED_BareMetal_Driver.git](https://github.com/akgozmirza/OLED_BareMetal_Driver.git)
