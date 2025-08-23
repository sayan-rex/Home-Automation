# Voice-Controlled Home Automation & Security System

A low-cost IoT solution to control and monitor home appliances using **Google Assistant**, **NodeMCU**, **IFTTT**, and the **Blynk app**. This project includes:

- Voice control via Google Assistant + IFTTT
- Blynk app dashboard for real-time monitoring
- Temperature and humidity sensing with DHT11
- PIR motion sensor for intruder alerts
- Flame sensor with fire detection alert
- Ultrasonic sensor for water level monitoring
- Automated fan and pump control

---

## Features

- Control light, fan, and water pump with voice commands
- Live temperature, humidity, water level, fire alert status on Blynk
- Fire detection with buzzer + app alert
- Motion detection with notification
- Automatic water pump control

---

## Required Apps

- [Blynk Legacy App (Android)](https://play.google.com/store/apps/details?id=cc.blynk)
- [IFTTT](https://ifttt.com)
- Google Assistant

---

## Hardware Required

| Component        | Quantity |
|------------------|----------|
| NodeMCU ESP8266  | 1        |
| DHT11 Sensor     | 1        |
| PIR Sensor       | 1        |
| Flame Sensor     | 1        |
| Ultrasonic Sensor| 1        |
| Relay Module     | 3        |
| Buzzer           | 1        |
| Jumper Wires     | -        |
| Breadboard       | 1        |

---

## Virtual Pin Mapping (Blynk)

| Widget          | Pin  | Function             |
|------------------|------|----------------------|
| Button           | V0   | Light Control        |
| Button           | V1   | Fan Control          |
| Button           | V2   | Water Pump Control   |
| Switch           | V3   | PIR Alert Toggle     |
| Display          | V4   | Temperature (°C)     |
| Display          | V5   | Humidity (%)         |
| Display          | V6   | Water Level (cm)     |
| LED Widget       | V7   | Fire Alert Indicator |

---

## IFTTT Setup

1. Create an IFTTT account
2. Create Applet: "If Google Assistant → Then Webhook"
3. Webhook URL:
