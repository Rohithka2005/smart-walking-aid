# Limitations, Scope, and Safety Notes

## Scope represented by the supplied slides

The material describes an ESP32 prototype that reads two digital IR inputs, measures front distance with an ultrasonic sensor, reads an ADXL345 accelerometer, shows distance/state on a 16x2 LCD, and switches an LED for obstacle or fall-heuristic states. An ESP32 local Wi-Fi access point serves a /fall endpoint. The described MIT App Inventor workflow polls the endpoint and is intended to send an SMS containing the phone's location after a FALL response.

## Functionality not evidenced by the supplied firmware

- **Directional vibration feedback:** mentioned in the aim, but no vibration motor/driver pins or output logic are defined.
- **GPS receiver on the cane:** no GPS hardware or firmware is shown. The described app obtains location from the phone.
- **Validated fall detection:** acceleration magnitude below 9 m/s² is an unvalidated heuristic and cannot reliably distinguish a fall from normal motion, tilt, or sensor disturbance.
- **Certified mobility aid:** no certification, user trial, reliability result, or formal safety assessment was supplied.
- **Measured performance:** no experimental results were supplied, so no detection accuracy, latency, range, battery-life, or test-success claims are made here.
- **Complete mobile app:** no MIT App Inventor .aia project was supplied.

## Safety precautions

1. Do not use this prototype as a replacement for a white cane, guide dog, human assistance, or another established mobility aid.
2. Keep testing on a bench with stationary obstacles. Do not stage a real fall or put a person at risk.
3. Protect ESP32 inputs. Many ultrasonic modules use 5 V ECHO levels; use suitable level shifting if required.
4. Change the demonstration Wi-Fi password before any use outside a controlled bench setup.
5. Treat SMS and phone GPS as best-effort. Location may be inaccurate, permissions may be denied, and carrier delivery can fail.
6. The ESP32 access point does not itself provide internet access. Verify location/SMS behavior on the intended phone.
7. Do not rely on the LED or LCD as a safety-critical warning. Sensors, wiring, power, latency, and software can fail.
8. Validate module voltages, mechanical mounting, and battery arrangements before carrying the prototype.

## Before claiming the project is complete

- Verify each sensor individually and record actual test data.
- Confirm ultrasonic accuracy and IR logic on the real modules.
- Test the app endpoint and SMS workflow on the intended phone.
- Validate any fall-detection method using a safe protocol and representative data.
- Add vibration feedback only after a suitable motor driver and control logic are designed and tested.
- Review the whole device with intended users and relevant domain experts before any real-world reliance.
