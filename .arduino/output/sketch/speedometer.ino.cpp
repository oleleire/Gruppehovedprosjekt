#include <Arduino.h>
#line 1 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
#include <Zumo32U4.h>
#include <Wire.h>

Zumo32U4Encoders encoder;
Zumo32U4Motors motors;
Zumo32U4OLED display;

const float countPerRotation = 75.81 * 12;


unsigned long leftEncoderCount = 0;
float rotationCount = 0;
float previousRotationCount = 0;

unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;

float centiPerSecond = 0;
float distance = 0; 
float rotationsPerSecond = 0;
float averageSpeed = 0; 


#line 24 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
float calculateRotation();
#line 30 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
float calculateRotationPerSecond();
#line 35 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
void setup();
#line 44 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
void displayValues();
#line 75 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
void displayValues2();
#line 84 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
void loop();
#line 24 "/Users/oleleire/Documents/ESI/Prosjektfag/Prosjekter /Gruppehovedprosjekt/speedometer/speedometer.ino"
float calculateRotation()
{
    float rotationCounter = leftEncoderCount / countPerRotation;
    return rotationCounter;
}

float calculateRotationPerSecond()
{
    return rotationCount - previousRotationCount;
}

void setup()
{
    encoder.init();
    display.init();
    display.clear();
    display.setLayout21x8();
    Serial.begin(115000);
}

void displayValues(){
    display.gotoXY(0,0);
    display.print("Speed:");
    display.gotoXY(0,1);
    display.print(centiPerSecond);
    display.print("cm/s");
    display.gotoXY(0, 6);
    display.print("Distance:");
    display.gotoXY(0,7);
    display.print(distance);
    display.print("m");
    

    

    display.gotoXY(16,0);
    display.print("Money");
    display.gotoXY(11,1);
    display.print("Used:");
    display.gotoXY(17,1);
    display.print("4kr");
    display.gotoXY(9,2);
    display.print("Earned:");
    display.gotoXY(17,2);
    display.print("2kr");
    display.gotoXY(10,3);
    display.print("Total:");
    display.gotoXY(17,3);
    display.print("7kr");
}

void displayValues2(){
    display.clear();
    display.gotoXY(0,0);
    display.print("Snitthastighet:");
    display.gotoXY(0,1);
    display.print(averageSpeed);
    display.print("cm/s");
}

void loop()
{
    motors.setSpeeds(150, 150);

    leftEncoderCount += encoder.getCountsAndResetLeft();
    rotationCount = calculateRotation();
    Serial.println(leftEncoderCount);

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 100)
    {
        previousMillis = currentMillis;
        rotationsPerSecond = calculateRotationPerSecond() * 10;
        previousRotationCount = rotationCount;
    }
    centiPerSecond = rotationsPerSecond * PI * 3.75;
    distance = rotationCount * 3.75* PI/100;
    averageSpeed = distance / 10;
    
    
    displayValues();

    unsigned long currentMillis1 = millis();
    
    if (currentMillis1 - previousMillis1 >= 10000)
    {
        
        previousMillis1 = currentMillis1;
        displayValues2();
        Serial.println(averageSpeed);
    }

}
