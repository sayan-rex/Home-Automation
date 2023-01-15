#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = ""; // Enter your Auth token
char ssid[] = ""; // Enter your WIFI name
char pass[] = ""; // Enter your WIFI password

DHT dht(D8, DHT11); //(sensor pin,sensor type)
BlynkTimer timer;
bool pirbutton = 0;

#define Buzzer D0
#define flame D1
#define PIR D7
#define trig D5
#define echo D6
#define LED D2
#define motor D4
#define pwm D3 // GPIO 0

byte degree[8] =
    {
        0b00011,
        0b00011,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000};

BLYNK_WRITE(V0)
{
    pirbutton = param.asInt();
}

void setup()
{
    Serial.begin(9600);
    pinMode(Buzzer, OUTPUT);
    pinMode(flame, INPUT);
    pinMode(PIR, INPUT);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(LED, OUTPUT);
    pinMode(motor, OUTPUT);
    pinMode(pwm, OUTPUT);
    digitalWrite(LED, HIGH);
    digitalWrite(motor, HIGH);
    analogWrite(pwm, 255);
    Blynk.begin(auth, ssid, pass);
    dht.begin();
    timer.setInterval(1000L, DHT11sensor);
    timer.setInterval(1000L, flamesensor);
    timer.setInterval(1000L, pirsensor);
    timer.setInterval(1000L, ultrasonic);
}

void DHT11sensor()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    if (t < 28)
    {
        analogWrite(9, 0);
        delay(100);
    }

    else if (t >= 28 && t <= 29)
    {
        analogWrite(pwm, 51);

        delay(100);
    }

    else if (t >= 29 && t <= 30)
    {
        analogWrite(pwm, 102);

        delay(100);
    }

    else if (t >= 30 && t <= 31)
    {
        analogWrite(pwm, 153);

        delay(100);
    }

    else if (t >= 31 && t <= 32)
    {
        analogWrite(pwm, 204);

        delay(100);
    }
    else if (t >= 32)
    {
        analogWrite(pwm, 255);

        delay(100);
    }
    delay(3000);

    Blynk.virtualWrite(V2, t);
    Blynk.virtualWrite(V3, h);
}

void flamesensor()
{
    bool value = digitalRead(flame);
    if (value == 1)
    {
        digitalWrite(Buzzer, LOW);
    }
    else if (value == 0)
    {
        Blynk.notify("Warning! Fire was detected");
        digitalWrite(Buzzer, HIGH);
    }
}
void pirsensor()
{
    bool value = digitalRead(PIR);
    if (pirbutton == 1)
    {
        if (value == 0)
        {
            digitalWrite(LED, LOW);
        }
        else if (value == 1)
        {
            Blynk.notify("Warning! Please check your security system");
            digitalWrite(LED, HIGH);
        }
    }
}

void ultrasonic()
{
    digitalWrite(trig, LOW);
    delayMicroseconds(4);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    long t = pulseIn(echo, HIGH);
    long cm = t / 29 / 2;
    if (cm < 5)
    {
        digitalWrite(motor, LOW);
        delay(1000);
    }

    else if (cm > 60)
    {

        digitalWrite(motor, HIGH);
        delay(1000);
    }
    Blynk.virtualWrite(V4, cm);
}

void loop()
{
    Blynk.run();
    timer.run();
}