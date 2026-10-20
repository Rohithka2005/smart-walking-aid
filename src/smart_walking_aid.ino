/*
  Smart Walking Aid with Obstacle Detection
  Based on the implementation described in the supplied project slides.
  Prototype only. See docs/limitations_and_safety.md.

  ESP32 + left/right active-LOW IR sensors + ultrasonic distance sensor +
  ADXL345 + 16x2 LCD + LED + local Wi-Fi endpoint for phone-app polling.
*/

#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <math.h>

const char* AP_SSID = "SmartStickESP";
const char* AP_PASSWORD = "12345678";  // Demo only: change before deployment.
WiFiServer server(80);

constexpr uint8_t IR_LEFT_PIN = 34;
constexpr uint8_t IR_RIGHT_PIN = 35;
constexpr uint8_t TRIG_PIN = 5;
constexpr uint8_t ECHO_PIN = 18;
constexpr uint8_t LED_PIN = 2;

LiquidCrystal lcd(14, 12, 13, 4, 25, 26);
Adafruit_ADXL345_Unified accelerometer = Adafruit_ADXL345_Unified(123);

constexpr long FRONT_OBSTACLE_CM = 30;
constexpr unsigned long ECHO_TIMEOUT_US = 30000UL;
constexpr float FALL_MAGNITUDE_THRESHOLD_MS2 = 9.0f; // Unvalidated heuristic.

bool fallDetected = false;

void printLcdLine(uint8_t row, const String& message) {
  lcd.setCursor(0, row);
  String padded = message;
  while (padded.length() < 16) padded += ' ';
  lcd.print(padded.substring(0, 16));
}

long readUltrasonicDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  const unsigned long duration = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);
  if (duration == 0) return 400; // Can mask a sensor failure as a clear path.
  return static_cast<long>((duration * 0.0343f) / 2.0f);
}

void handlePhoneRequest() {
  WiFiClient client = server.available();
  if (!client) return;

  client.setTimeout(1000);
  const String requestLine = client.readStringUntil('\r');
  Serial.print("HTTP request: ");
  Serial.println(requestLine);
  while (client.available()) client.read();

  if (requestLine.indexOf("/fall") >= 0) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/plain; charset=utf-8");
    client.println("Connection: close");
    client.println();
    client.println(fallDetected ? "FALL" : "SAFE");
  } else {
    client.println("HTTP/1.1 404 Not Found");
    client.println("Content-Type: text/plain; charset=utf-8");
    client.println("Connection: close");
    client.println();
    client.println("Use /fall");
  }
  delay(1);
  client.stop();
}

void setup() {
  Serial.begin(115200);
  pinMode(IR_LEFT_PIN, INPUT);
  pinMode(IR_RIGHT_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  lcd.begin(16, 2);
  printLcdLine(0, "Smart Stick");
  printLcdLine(1, "Starting...");
  delay(1500);

  Wire.begin(21, 22);
  if (!accelerometer.begin()) {
    Serial.println("ERROR: ADXL345 not found. Check power and I2C wiring.");
    printLcdLine(0, "ADXL345 ERROR");
    printLcdLine(1, "Check wiring");
    while (true) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      delay(250);
    }
  }

  if (!WiFi.softAP(AP_SSID, AP_PASSWORD)) {
    Serial.println("ERROR: ESP32 access point failed to start.");
    printLcdLine(0, "WiFi AP ERROR");
    printLcdLine(1, "Check setup");
    while (true) delay(1000);
  }

  server.begin();
  Serial.println("ESP32 hotspot started.");
  Serial.print("Connect phone to: ");
  Serial.println(AP_SSID);
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.println("App endpoint: http://192.168.4.1/fall");
  printLcdLine(0, "Smart Stick ON");
  printLcdLine(1, "WiFi: SmartStick");
  delay(1000);
}

void loop() {
  sensors_event_t event;
  accelerometer.getEvent(&event);
  const long distanceCm = readUltrasonicDistanceCm();
  const bool leftObstacle = digitalRead(IR_LEFT_PIN) == LOW;
  const bool rightObstacle = digitalRead(IR_RIGHT_PIN) == LOW;
  const bool frontObstacle = distanceCm < FRONT_OBSTACLE_CM;

  const float totalAcceleration = sqrtf(
      event.acceleration.x * event.acceleration.x +
      event.acceleration.y * event.acceleration.y +
      event.acceleration.z * event.acceleration.z);
  fallDetected = totalAcceleration < FALL_MAGNITUDE_THRESHOLD_MS2;

  Serial.print("Distance (cm): ");
  Serial.print(distanceCm);
  Serial.print(" | Acceleration magnitude (m/s^2): ");
  Serial.print(totalAcceleration, 2);
  Serial.print(" | Fall heuristic: ");
  Serial.println(fallDetected ? "FALL" : "SAFE");

  printLcdLine(0, "Dist: " + String(distanceCm) + " cm");
  if (fallDetected) {
    printLcdLine(0, "FALL DETECTED!");
    printLcdLine(1, "Sending Alert");
    digitalWrite(LED_PIN, HIGH);
  } else if (leftObstacle) {
    printLcdLine(1, "Obstacle Left");
    digitalWrite(LED_PIN, HIGH);
  } else if (rightObstacle) {
    printLcdLine(1, "Obstacle Right");
    digitalWrite(LED_PIN, HIGH);
  } else if (frontObstacle) {
    printLcdLine(1, "Obstacle Front");
    digitalWrite(LED_PIN, HIGH);
  } else {
    printLcdLine(1, "Path Clear");
    digitalWrite(LED_PIN, LOW);
  }

  handlePhoneRequest();
  delay(200);
}
