# Component List and Bill of Materials

This list is reconstructed only from the supplied project slides and firmware pin definitions. Exact module models, part numbers, prices, and complete power specifications were not provided.

| Component | Quantity | Role | Details to confirm before assembly |
|---|---:|---|---|
| ESP32 development board | 1 | Sensor processing and local Wi-Fi HTTP server | Exact board variant and available GPIO pins |
| Digital IR obstacle sensor | 2 | Left/right obstacle indications | Model, range, output voltage, and whether LOW means obstacle |
| Ultrasonic distance sensor | 1 | Front distance measurement | Exact model, supply voltage, and ECHO signal level |
| ADXL345 accelerometer module | 1 | Reads acceleration over I2C | Module voltage and I2C configuration |
| 16x2 LCD | 1 | Shows distance and status | Interface type, supply, contrast, and logic compatibility |
| LED indicator | 1 / board-dependent | Visual alert | Whether GPIO 2 is connected to an onboard LED |
| Suitable power source | 1 | Powers prototype | Required voltage/current and runtime |
| Jumper wires/connectors | As needed | Interconnections | Secure mounting, strain relief, common ground |
| Android phone | 1 | Runs described MIT App Inventor workflow | Location permissions, SMS support, Wi-Fi behavior |

## GPIO mapping

| ESP32 GPIO | Connection |
|---:|---|
| 34 | Left IR digital output |
| 35 | Right IR digital output |
| 5 | Ultrasonic TRIG |
| 18 | Ultrasonic ECHO, with a suitable voltage interface if required |
| 2 | LED indicator |
| 21 | ADXL345 SDA |
| 22 | ADXL345 SCL |
| 14 | LCD RS |
| 12 | LCD Enable |
| 13 | LCD D4 |
| 4 | LCD D5 |
| 25 | LCD D6 |
| 26 | LCD D7 |

The slides do not provide a full schematic, exact power wiring, or a vibration motor circuit. Do not purchase or wire a vibration driver based on this document alone.

## Electrical checks before powering

- Confirm the ultrasonic ECHO voltage. Many modules output 5 V; an ESP32 input uses 3.3 V logic, so suitable level shifting may be required.
- Check the selected LCD's supply and 3.3 V logic compatibility from its documentation.
- Verify each module's supply voltage from its datasheet; do not assume 3.3 V and 5 V are interchangeable.
- The code assumes IR output LOW means obstacle. Verify this on the physical module.
- ESP32 variants differ; the pin table only matches the assignments in the supplied slides.
- The slide deck does not specify a vibration motor driver or power circuit.
