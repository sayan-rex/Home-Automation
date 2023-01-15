# Voice Recognition System Controlled Home Automation

Home automation allows us to control household appliances like light, motor, fan etc. It also provides home security and emergency system to be activated. The proposed project uses NodeMCU board with internet being remotely controlled by an Android OS smartphone. It is also used for monitoring by sensing and analyzing data about temperature, humidity, water level, and fire. Google assistant has been used to control light, fan and the water pump by saying Ok google, turn the light ON or OFF. Google Assistant to control our home appliances by giving common language voice directions and with the assistance of IFTTT (If This Then That) application the directions are decoded and afterward sent to the Node microcontroller. Blynk app which create virtual switches linked with IFTTT, used to analyzing data of all the appliances are connected over the internet using Wi-Fi which puts this system under the IOT. This system also works for the security purpose, if any inevitable incident happens, the user will immediately receive alert message/mail in their smart phone. 

The system has been modelled to monitor data from four sensor-modules and control three loads by using a mobile application. In the proposed circuit the NodeMCU (Microcontroller Unit) reads sensor data and sends them to mobile application for processing. It also receives command from mobile application to control home appliances through relay-module according to the user requirement. Internet server-Blynk mobile application in smartphone and NodeMCU communicated by using Blynk server. Bidirectional transfer of data between NodeMCU and mobile app occurs through this server. Google assistant has been used to use voice control in this project. Blynk account, a cloud based free IoT web server has been used to create virtual switches. It has been also linked to IFTTT (IF This Then That) website which is used to create if else conditional statements. Also, the voice commands for Google assistant have been added through IFTTT website. The switching modules have been used for turning light on/off, turning the fan on/off and turning water pump on/off. The output signal from NodeMCU activates and deactivates the relay to perform switching operation. The circuit works on AC phase chopping principle to control fan speed.

In this project we are designing an IoT based smart fan module too. To sense the room temperature, we have used DHTl 1 temperature sensor. According to the room temperature sensor output the NodeMCU Microcontroller control the speed of fan, and also used PIR sensor for detecting human motion to tun ON or tun OFF the Fan. 

An ultrasonic sensor HC-SR04 have been used to sense the tank water level, which uses sound waves to calculate the distance as s=0.0343*(T/2), where 0.03430 is the speed of sound in air in cm/microsecond and T is time taken for transmission and reception of reflected sound wave. The Blynk App has widgets in it like a display for displaying messages or distance or any parameter, which can be done using NodeMCU command.
The fire sensor is connected at one pin to give the digital input to the and Buzzer is connected at the other pin to get digital output from the NodeMCU. If fire is detected by the fire sensor, then it gives "O" turns on the buzzer, sends notification to the mobile and a mail to the attached mail address. The hardware and software required for the overall implementation of this project are NODEMCU, (ESP8266), DHT-11 Sensor, PIR Sensor, Ultrasonic Sensor, Flame Sensor, Buzzer, Relay Module, Mobile phone, Power supply board, wire, Blynk (mobile application), IFTTT (Mobile application), and ArduinoIDE. 
