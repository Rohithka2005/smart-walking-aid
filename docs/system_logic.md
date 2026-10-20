# System Logic

## Startup sequence represented in the supplied sketch

1. Initialize serial communication at 115200 baud.
2. Configure IR pins, ultrasonic trigger/echo pins, and LED.
3. Initialize the 16x2 LCD.
4. Start I2C on SDA 21 and SCL 22, then initialize the ADXL345.
5. If the ADXL345 is not found, print an error and halt normal operation.
6. Start the ESP32 access point SmartStickESP and an HTTP server on port 80.

## Repeating loop

1. Read acceleration X/Y/Z from the ADXL345.
2. Read front distance with the ultrasonic sensor.
3. Read left/right IR digital outputs; the code assumes LOW means obstacle.
4. Calculate acceleration magnitude: sqrt(x² + y² + z²).
5. Set the prototype fall flag if magnitude is below 9 m/s².
6. Update the LCD and LED. Priority is possible fall, left obstacle, right obstacle, front obstacle, then clear-path display.
7. Check for phone HTTP requests and wait 200 ms.

## Ultrasonic range calculation

The source code sends a short trigger pulse and measures the echo pulse duration. Distance in centimetres is calculated as duration × 0.0343 / 2. A missing echo returns 400 cm in the supplied design; this can look like a clear path even when the sensor is disconnected or failing.

## HTTP endpoint

The server checks for a request containing /fall and responds with plain text:
- FALL: the acceleration threshold flag is true.
- SAFE: the acceleration threshold flag is false.

This simple threshold is not a validated fall classifier. The endpoint is a local demo interface only.
