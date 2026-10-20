# Hardware and Wiring Reference

This guide is reconstructed only from the supplied project slides and code. Confirm the exact module models and LCD pin order on the actual hardware before powering it.

## Components represented in the source material

| Component | Qty. | Role | Evidence |
|---|---:|---|---|
| ESP32 development board | 1 | Sensor processing and local HTTP endpoint | Wi-Fi library and server |
| Digital IR obstacle sensor | 2 | Left/right obstacle indication | GPIO 34/35, active-LOW assumption |
| Ultrasonic sensor | 1 | Front obstacle distance | TRIG GPIO 5, ECHO GPIO 18 |
| ADXL345 accelerometer | 1 | Acceleration magnitude heuristic | I2C SDA 21 / SCL 22 |
| 16x2 LCD | 1 | Distance and status | LiquidCrystal(14, 12, 13, 4, 25, 26) |
| LED indicator | 1 / board-dependent | Visual alert | GPIO 2 |
| Wires and power source | As needed | Connections and operation | Exact ratings not specified |
| Android phone | 1 | Polls /fall, described location/SMS workflow | App workflow from slides |

## Pin map

| ESP32 pin | Connect to | Notes |
|---|---|---|
| GPIO 34 | Left IR digital OUT | Code interprets LOW as obstacle; input-only on classic ESP32 |
| GPIO 35 | Right IR digital OUT | Code interprets LOW as obstacle; input-only on classic ESP32 |
| GPIO 5 | Ultrasonic TRIG | Configured as output |
| GPIO 18 | Ultrasonic ECHO | Input; voltage interface may be required |
| GPIO 2 | LED / board LED | Board LED availability varies |
| GPIO 21 | ADXL345 SDA | I2C |
| GPIO 22 | ADXL345 SCL | I2C |
| GPIO 14 | LCD RS | Parallel interface |
| GPIO 12 | LCD Enable | Parallel interface |
| GPIO 13 | LCD D4 | Parallel interface |
| GPIO 4 | LCD D5 | Parallel interface |
| GPIO 25 | LCD D6 | Parallel interface |
| GPIO 26 | LCD D7 | Parallel interface |

## Electrical safety checks

- Many HC-SR04-style sensors output ECHO near 5 V. ESP32 GPIO inputs are 3.3 V logic; add an appropriate divider/level shifter if the chosen module requires it.
- Verify the selected LCD's supply and 3.3 V logic compatibility. Its exact model is not specified.
- Verify each module's supply voltage from its datasheet; do not assume 3.3 V and 5 V are interchangeable.
- The code assumes IR output LOW means obstacle. Verify this on the physical module.
- ESP32 variants differ; the pin table only matches the assignments in the supplied slides.
- The slide deck does not specify a vibration motor driver or power circuit.

## Assembly checklist

1. Disconnect power before wiring.
2. Connect the IR outputs to GPIO 34 and 35 and establish common ground.
3. Connect TRIG to GPIO 5 and ECHO through appropriate protection to GPIO 18 if needed.
4. Connect the ADXL345 to GPIO 21/22 and verify its supply.
5. Wire the LCD as shown and confirm contrast/power requirements.
6. Connect/verify the LED on GPIO 2 only if supported by the selected board.
7. Power the board, open Serial Monitor at 115200 baud, and check startup messages before app testing.
