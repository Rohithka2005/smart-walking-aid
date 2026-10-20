# Testing and Validation Checklist

No measured test results were present in the supplied slides. Use this checklist to record observations after safe bench testing. Do not mark checks as passed until they are actually performed.

| Test | Procedure | Record |
|---|---|---|
| Startup | Power the ESP32 and open Serial Monitor at 115200 baud | Board, startup messages, pass/fail |
| ADXL345 detection | Check initialization and I2C wiring | Detected/not detected, wiring notes |
| Left IR input | Place a stationary object within sensor range | Output level, observed LCD state |
| Right IR input | Place a stationary object within sensor range | Output level, observed LCD state |
| Ultrasonic distance | Test at measured distances with stationary objects | Reference distance, measured distance, error |
| Front threshold | Move a stationary object across the 30 cm prototype threshold | State changes and distance |
| LCD | Check distance, left/right/front, and fall messages | Observed text and any stale characters |
| LED | Check alert and clear-path branches | On/off behavior |
| HTTP endpoint | Connect phone and request /fall | Status code and response text |
| App polling | Verify each 5-second request and error handling | Request interval, disconnect response |
| SMS workflow | Use a consenting test recipient and test message | Permission, send status, received/not received |
| Location | Verify phone latitude/longitude and accuracy display | Location available, estimated accuracy |
| Repeated alert prevention | Simulate repeated FALL responses safely using controlled test data | Number of SMS messages per event |

## Safety and reporting guidance

- Test on a bench with stationary obstacles. Do not conduct tests that risk a person falling.
- Record the exact board, sensor module model, supply voltage, environment, and software version.
- Report actual values only; don't invent range, accuracy, latency, battery-life, or fall-detection statistics.
- A successful bench test is not proof of reliability in crowded, outdoor, or user mobility settings.
