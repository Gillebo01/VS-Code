#include <Zumo32U4.h>
#include <Wire.h>
#include <EEPROM.h>

#define DEBUG_CHARGER_LINK
#include "ChargerLink/ChargerLink.h"

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonB buttonC;
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4Encoders encoders;
Zumo32U4OLED display;

int carId = 0;
unsigned long lastMillis = 0;
unsigned long lastMillisBat = 0;
float motorSpeed = 0;
long lastPos = 0;
float lastPosBat = 0;
long travel = 0;
float batteryLevel = 100;
int batteryLevelWatch = 0;
float batteryHealth = 100;
int batteryHealthWatch = 0;
float batteryDrain = 0;
const char encoderErrorLeft[] PROGMEM = "!<c2";
const char encoderErrorRight[] PROGMEM = "!<e2";
long totCountsLeft = 0;
long totCountsRight = 0;
int boost = 0;
int cState = 0;
int PROXIMITY = 0;

ZumoIrSocket irSocket(22, carId, LEFT_IR);
ChargerLink chargerLink(irSocket);

// Sensor values will go in this array
unsigned int lineSensorValues[5];

int speed1 = 220;

void setup()
{
        Serial.begin(9600);
        Serial.begin(115200);
        irSocket.begin();
        // EEPROM.write(0,0);
        buttonA.waitForButton();
        // Initialize the sensors, and turn on the LEDs for them.
        lineSensors.initFiveSensors();
        lineSensors.emittersOn();
        proxSensors.initFrontSensor();
        // Calibrates the linesensors
        calibrate();
        if (EEPROM.read(0) > 0)
        {
                batteryHealth = EEPROM.read(0);
        }
        buttonB.waitForButton();
        delay(1000);
}

void calibrate()
{
        for (int i = 100; i < 150; i++)
        {
                motors.setSpeeds(i, -i);
                lineSensors.calibrate();
        }

        for (int i = 150; i > 0; i--)
        {
                motors.setSpeeds(i, -i);
                lineSensors.calibrate();
        }

        for (int i = 100; i < 150; i++)
        {
                motors.setSpeeds(-i, i);
                lineSensors.calibrate();
        }

        for (int i = 150; i > 0; i--)
        {
                motors.setSpeeds(-i, i);
                lineSensors.calibrate();
        }
}

void OLED()
{
        int16_t position = lineSensors.readLine(lineSensorValues);
        static uint8_t lastDisplayTime;

        if ((uint8_t)(millis() - lastDisplayTime) >= 200)
        {
                lastDisplayTime = millis();
                display.clear();
                display.setLayout21x8();
                display.gotoXY(0, 0);
                display.print(travel);
                display.gotoXY(5, 0);
                display.print("cm");

                display.gotoXY(0, 2);
                display.print(motorSpeed);
                display.gotoXY(5, 2);
                display.print("cm/s");

                display.gotoXY(0, 4);
                display.print(round(batteryLevel), 1);
                display.gotoXY(5, 4);
                display.print("%");

                display.gotoXY(0, 6);
                display.print(round(batteryHealth), 1);
                display.gotoXY(5, 6);
                display.print("%");
        }
}

void calculations()
{
        totCountsLeft += encoders.getCountsAndResetLeft();
        totCountsRight += encoders.getCountsAndResetRight();

        travel = abs(((totCountsLeft + totCountsRight) / 2) / 7.9 / 10);

        unsigned long currentMillis = millis();
        float currentPos = (totCountsLeft + totCountsRight) / 2;
        if (currentMillis - lastMillis >= 100)
        {
                motorSpeed = abs((((currentPos - lastPos) / 7.9) / (currentMillis - lastMillis)) * 100);
                if (batteryLevel > 0 and motorSpeed > 20)
                {
                        batteryLevel -= 0.01 + (currentPos - lastPos) / 100000 * motorSpeed;
                        batteryHealth -= abs((0.01 + (currentPos - lastPos) / 100000 * motorSpeed) / 100);
                }

                if (batteryLevel > 0 and motorSpeed < 20)
                {
                        batteryLevel -= 0.01 + (currentPos - lastPos) / 1000000 * motorSpeed;
                        batteryHealth -= abs((0.01 + (currentPos - lastPos) / 1000000 * motorSpeed) / 10);
                }

                if (batteryLevel < 20 and ((currentPos - lastPos) < 0))
                {
                        batteryLevel -= 0.01 + 10 * ((currentPos - lastPos) / 10000 * motorSpeed);
                }

                lastMillis = currentMillis;
                lastPos = currentPos;
                EEPROM.write(0, batteryHealth);
        }
        // Serial.println(motorSpeed);
        // Serial.println(batteryLevel);
}

void RUN()
{
        tooClose();
        int16_t position = lineSensors.readLine(lineSensorValues);

        if (PROXIMITY < 5)
        {

                // Mid
                if (1700 < position < 2300)
                {
                        motors.setSpeeds(speed1, speed1);
                }

                // Høyre

                if (position < 1700)
                {
                        motors.setSpeeds(speed1 * 0.5, speed1 * 1.5);
                }

                if (position <= 1000)
                {
                        motors.setSpeeds(speed1 * 0.25, speed1 * 2);
                }

                // Venstre

                if (position > 2300)
                {
                        motors.setSpeeds(speed1 * 1.5, speed1 * 0.5);
                }

                if (position >= 3000)
                {
                        motors.setSpeeds(speed1 * 2, speed1 * 0.25);
                }
        }
        else
        {
                motors.setSpeeds(0, 0);
        }
}

void chargeBoost()
{
        int cState = buttonB.getSingleDebouncedPress();
        if (cState)
        {
                boost += 1;
                delay(1000);
        }

        if (boost == 1)
        {
                if (batteryLevel < 20)
                {
                        motors.setSpeeds(-100, -100);
                }
        }

        if (boost == 1 and batteryLevel >= 20)
        {
                boost += 1;
        }
}

void batterydependentRUN()
{
        if (batteryLevel > 20)
        {
                batteryLevelWatch = 1;
        }
        if (batteryLevel <= 20 and batteryLevel > 0)
        {
                batteryLevelWatch = 2;
        }
        if (batteryLevel <= 0)
        {
                batteryLevelWatch = 3;
        }

        switch (batteryLevelWatch)
        {
        case 1:
                (speed1 = speed1);
                break;

        case 2:
                (speed1 = 100);
                break;

        case 3:
                (speed1 = 0);
                break;
        }
}

void tooClose()
{
        proxSensors.read();
        int proxValLeft = proxSensors.countsFrontWithLeftLeds();
        int proxValRight = proxSensors.countsFrontWithRightLeds();

        PROXIMITY = (proxValLeft + proxValRight) / 2;
}

void updateChargerLink()
{
        if (chargerLink.read())
        {
                if (chargerLink.signal == ChargerLinkSignal::LINK_AVAILABLE)
                {
                        Serial.println("Detected charger link!");
                }

                if (chargerLink.signal == ChargerLinkSignal::BALANCE)
                {
                        Serial.println(chargerLink.balance);
                }
        }
}

void updateButton()
{
        if (buttonA.getSingleDebouncedPress())
        {
                Serial.println("Added 20 to balance!");
                chargerLink.addEarnings(20);
        }
}

void loop()
{
        RUN();
        chargeBoost();
        OLED();
        calculations();
        batterydependentRUN();
        updateChargerLink();
        updateButton();
}