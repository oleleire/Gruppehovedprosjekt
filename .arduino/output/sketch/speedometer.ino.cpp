#include <Arduino.h>
#line 1 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
Ollo
ollo0462

Ev1 — Today at 1:08 PM
#include <Zumo32U4.h>
#include <Wire.h>

Zumo32U4Encoders encoder;
Zumo32U4Motors motors;

const float countPerRotation = 75.81 * 12;
const float wheelDiameter = 3.75;

int leftEncoderCount = 0;
float rotationCount = 0;
float previousRotationCount = 0;

unsigned long previousMillis = 0;
float rotationsPerSecond = 0;
float cmPerSecond = 0;
float distanceTraveled = 0;

#line 23 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
float calculateRotation();
#line 29 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
float calculateRotationPerSecond();
#line 34 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
float calculateCmPerSecond();
#line 39 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
float calculateDistanceTraveled();
#line 44 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
void setup();
#line 49 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
void loop();
#line 23 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
float calculateRotation()
{
    float rotationCounter = leftEncoderCount / countPerRotation;
    return rotationCounter;
}

float calculateRotationPerSecond()
{
    return rotationCount - previousRotationCount;
}

float calculateCmPerSecond()
{
    return 2 * PI * (wheelDiameter / 2) * rotationsPerSecond;
}

float calculateDistanceTraveled()
{
    return cmPerSecond * (millis() / 1000);
}

void setup()
{
    encoder.init();
}

void loop()
{
    motors.setSpeeds(200, 200);

    leftEncoderCount += encoder.getCountsAndResetLeft();
    rotationCount = calculateRotation();

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 10)
    {
        previousMillis = currentMillis;
        rotationsPerSecond = calculateRotationPerSecond() * 100;
        previousRotationCount = rotationCount;
    }
    cmPerSecond = calculateCmPerSecond();
    distanceTraveled = calculateDistanceTraveled();
}
Ollo — Today at 1:08 PM
﻿
Ev1
Ev1#0630
