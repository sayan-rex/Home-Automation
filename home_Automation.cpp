// Home Automation Main Controller
// Author: Sayan Rex
// Repository: https://github.com/sayan-rex/Home-Automation
// Description: ESP8266-based IoT system for smart home control via Blynk platform
// ===============================================================================

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// =================== Credentials ===================
constexpr char AUTH_TOKEN[] = "Your_Blynk_Auth_Token";
constexpr char WIFI_SSID[] = "Your_WiFi_SSID";
constexpr char WIFI_PASS[] = "Your_WiFi_Password";

// =================== Pin Definitions ===================
constexpr uint8_t RELAY_LIGHT   = D0; // GPIO16
constexpr uint8_t RELAY_FAN     = D1; // GPIO5
constexpr uint8_t RELAY_PUMP    = D2; // GPIO4
constexpr uint8_t DHTPIN        = D3; // GPIO0
constexpr uint8_t FLAME_SENSOR  = D4; // GPIO2
constexpr uint8_t BUZZER        = D5; // GPIO14
constexpr uint8_t PIR_SENSOR    = D6; // GPIO12
constexpr uint8_t TRIG_PIN      = D7; // GPIO13
constexpr uint8_t ECHO_PIN      = D8; // GPIO15

// =================== DHT Sensor Setup ===================
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

// =================== State Variables ===================
bool pirAlertEnabled = true;
unsigned long lastMotionAlert = 0;
unsigned long lastFlameAlert = 0;
constexpr unsigned long ALERT_DELAY = 10000UL; // 10 sec cooldown

// =================== Blynk Virtual Pins ===================
/*
V0 - Button: Light (RELAY_LIGHT)
V1 - Button: Fan (RELAY_FAN)
V2 - Button: Pump (RELAY_PUMP)
V3 - Switch: PIR Motion Alerts ON/OFF
V4 - Display: Temperature
V5 - Display: Humidity
V6 - Display: Water Level
V7 - LED: Fire Alert Indicator
*/

// =================== Blynk Controls ===================
BLYNK_WRITE(V0) { digitalWrite(RELAY_LIGHT, param.asInt()); }
BLYNK_WRITE(V1) { digitalWrite(RELAY_FAN, param.asInt()); }
BLYNK_WRITE(V2) { digitalWrite(RELAY_PUMP, param.asInt()); }
BLYNK_WRITE(V3) { pirAlertEnabled = param.asInt(); }

void setup() {
  Serial.begin(9600);

  // Pin Setup
  pinMode(RELAY_LIGHT, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_PUMP, OUTPUT);
  pinMode(FLAME_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(PIR_SENSOR, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Default States
  digitalWrite(RELAY_LIGHT, LOW);
  digitalWrite(RELAY_FAN, LOW);
  digitalWrite(RELAY_PUMP, LOW);
  digitalWrite(BUZZER, LOW);

  dht.begin();
  Blynk.begin(AUTH_TOKEN, WIFI_SSID, WIFI_PASS);

  // Timed Tasks
  timer.setInterval(2000L, readDHT);
  timer.setInterval(1000L, checkFlame);
  timer.setInterval(1000L, checkPIR);
  timer.setInterval(3000L, checkWaterLevel);
}

// =================== DHT11 Temp & Humidity ===================
void readDHT() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("[Error] Failed to read from DHT sensor");
    return;
  }

  Serial.print("Temperature: "); Serial.print(temperature); Serial.print(" °C | ");
  Serial.print("Humidity: "); Serial.println(humidity);

  Blynk.virtualWrite(V4, temperature);
  Blynk.virtualWrite(V5, humidity);

  // Auto Fan Control Logic
  if (temperature >= 32.0) digitalWrite(RELAY_FAN, HIGH);
  else if (temperature <= 28.0) digitalWrite(RELAY_FAN, LOW);
}

// =================== Flame Detection ===================
void checkFlame() {
  int flame = digitalRead(FLAME_SENSOR);
  if (flame == LOW) {
    digitalWrite(BUZZER, HIGH);
    if (millis() - lastFlameAlert > ALERT_DELAY) {
      Blynk.notify("🔥 Fire detected!");
      Blynk.virtualWrite(V7, 1);
      lastFlameAlert = millis();
    }
  } else {
    digitalWrite(BUZZER, LOW);
    Blynk.virtualWrite(V7, 0);
  }
}

// =================== PIR Motion Detection ===================
void checkPIR() {
  int motion = digitalRead(PIR_SENSOR);
  if (pirAlertEnabled && motion == HIGH) {
    if (millis() - lastMotionAlert > ALERT_DELAY) {
      Blynk.notify("🚨 Motion detected!");
      lastMotionAlert = millis();
    }
  }
}

// =================== Ultrasonic Water Level ===================
void checkWaterLevel() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration / 29 / 2;

  Serial.print("Water Level: "); Serial.print(distance); Serial.println(" cm");
  Blynk.virtualWrite(V6, distance);

  // Pump Control
  if (distance > 30 && distance < 200) {
    digitalWrite(RELAY_PUMP, HIGH);
  } else if (distance <= 10) {
    digitalWrite(RELAY_PUMP, LOW);
  }
}

void loop() {
  Blynk.run();
  timer.run();
}