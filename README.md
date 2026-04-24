# Smart Room System (Arduino)

## Description

Smart Room System is an automated control system based on Arduino that adjusts room conditions according to light intensity using an LDR sensor. The system controls lighting using PWM, opens and closes windows using a servo motor, and operates curtains using a DC motor with an L293D driver. It supports both automatic and manual modes, with real-time monitoring displayed on an LCD.

---

## Features

* AUTO and MANUAL modes
* Light detection using LDR (ADC input)
* PWM-based lighting control
* Servo-controlled window system
* DC motor curtain system using L293D driver
* Real-time monitoring via LCD

---

## Pin Configuration

| Component      | Arduino Pin | Description        |
| -------------- | ----------- | ------------------ |
| LDR            | A0          | Light sensor (ADC) |
| LED            | D3          | PWM lighting       |
| Servo          | D9          | Window control     |
| L293D ENA      | D10         | Motor speed (PWM)  |
| L293D IN1      | D7          | Motor direction    |
| L293D IN2      | D8          | Motor direction    |
| Button Mode    | D2          | Mode switch        |
| Button Window  | D4          | Servo control      |
| Button Curtain | D5          | Motor control      |
| LCD I2C        | A4, A5      | Display            |

---

## System Workflow

### Automatic Mode

* Bright → Light OFF, window OPEN, curtain moves forward
* Dark → Light ON, window CLOSED, curtain moves reverse
* Normal → Moderate operation

The DC motor operates for a few seconds and then stops automatically using a timer system.

---

### Manual Mode

* Mode Button → Switch AUTO / MANUAL
* Window Button → Open/Close window
* Curtain Button → Move curtain (DC motor)

```
---
## Project Documentation

**Source Code:** [Code.ino](./program.ino)
**Circuit Schematic:** [3D Schematics](./rangkaian.png)
**Simulation Video:** [Watch Here](https://youtu.be/272JC6ugsRw?si=4HL8MIg9y9PYzBdz)
**Circuit Simulation:** [Try On Tinkercad](link-tinkercad-kamu)

---

Developed by **Adrian Noval Saputra**
