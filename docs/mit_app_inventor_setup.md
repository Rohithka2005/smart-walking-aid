# MIT App Inventor Setup Guide

This document translates the app workflow described in the supplied slides into an implementation checklist. It is not a supplied or compiled MIT App Inventor project; no .aia file or complete block screenshots were provided.

## Expected behavior described in the slides

1. When the Connect button is pressed, show “Monitoring Started”, enable the phone LocationSensor, and start a timer.
2. Every 5 seconds, send an HTTP GET request to http://192.168.4.1/fall using the Web component while the phone is connected to the ESP32 access point.
3. When the response is FALL, show “Fall Detected”, get latitude/longitude from the phone's LocationSensor, and send an SMS to a configured emergency number.
4. Use an alert latch so one continuous FALL state does not send repeated SMS messages.
5. When the response is SAFE, clear the alert latch so a later, separate FALL state can trigger another SMS.
6. If a request fails, display “Connection Lost”. Do not describe connection loss as SAFE.

## Suggested components in MIT App Inventor

- Button: Connect / Start Monitoring.
- Label: Connection and monitoring status.
- Web component: request the local ESP32 endpoint.
- Clock component: timer interval set to 5000 ms.
- LocationSensor: reads phone latitude/longitude when permissions are granted.
- Texting component: sends the emergency SMS.
- Notifier: reports errors and permission issues.

## Request/response contract

- Request method: GET
- URL: http://192.168.4.1/fall
- Successful text response: FALL or SAFE
- Polling interval described in slides: 5 seconds

The ESP32 response indicates only its acceleration threshold flag. It does not transmit obstacle direction, distance, or coordinates, and SAFE does not mean the route is clear.

## Testing before enabling SMS

- Confirm phone can connect to the SmartStickESP access point.
- Open the endpoint in a browser and verify that a text response is returned.
- Confirm the app handles FALL, SAFE, timeout, and connection-loss cases.
- Test SMS only with a consenting test recipient and a clearly labelled test message.
- Check phone location permissions and whether location can be obtained in the intended environment.
- Avoid relying on this workflow for real emergencies until thoroughly validated.
