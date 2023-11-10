// Line Sensor Example
#include <Zumo32U4.h>
#include <Wire.h>

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4LineSensors lineSensors;
Zumo32U4Encoders encoders;
Zumo32U4ButtonB buttonB;
Zumo32U4OLED display;

unsigned long lastMillis = 0;
float motorSpeed = 0;
long lastPos = 0;
long travel = 0;
const char encoderErrorLeft[] PROGMEM = "!<c2";
const char encoderErrorRight[] PROGMEM = "!<e2";
long totCountsLeft = 0;
long totCountsRight = 0;
// Sensor values will go in this array
unsigned int lineSensorValues[5];
// int sensVal = 0;
int speed1 = 150;
// int speed2 = 150;
// int speed3 = 200;
// int mid = 2000;

void setup()
{
        Serial.begin(9600);
        buttonA.waitForButton();
        // Initialize the sensors, and turn on the LEDs for them.
        lineSensors.initFiveSensors();
        lineSensors.emittersOn();
        // Calibrates the linesensors
        calibrate();
        delay(1000);
}

void calibrate()
{
        for (int i = 100; i < 200; i++)
        {
                motors.setSpeeds(i, -i);
                lineSensors.calibrate();
        }

        for (int i = 200; i > 0; i--)
        {
                motors.setSpeeds(i, -i);
                lineSensors.calibrate();
        }

        for (int i = 100; i < 200; i++)
        {
                motors.setSpeeds(-i, i);
                lineSensors.calibrate();
        }

        for (int i = 200; i > 0; i--)
        {
                motors.setSpeeds(-i, i);
                lineSensors.calibrate();
        }
}

void OLED()
{
        int16_t position = lineSensors.readLine(lineSensorValues);
        static uint8_t lastDisplayTime;

        if ((uint8_t)(millis() - lastDisplayTime) >= 100)
        {
                lastDisplayTime = millis();
                display.clear();
                display.print(position);
                // display.print(countsLeft);
                // display.gotoXY(0, 1);
                // display.print(countsRight);
                display.gotoXY(5, 0);
                display.print(motorSpeed);
        }
}

void lenght()
{
        totCountsLeft += encoders.getCountsAndResetLeft();
        totCountsRight += encoders.getCountsAndResetRight();

        travel = ((totCountsLeft + totCountsRight) / 2) / 7.9 / 10;

        unsigned long currentMillis = millis();
        float currentPos = (totCountsLeft + totCountsRight) / 2;
        if (currentMillis - lastMillis >= 100)
        {
                motorSpeed = (((currentPos - lastPos) / 7.9) / (currentMillis - lastMillis)) * 100;

                lastMillis = currentMillis;
                lastPos = currentPos;
        }
        Serial.println(currentPos - lastPos);
}

void RUN()
{
        int16_t position = lineSensors.readLine(lineSensorValues);

        // Mid
        if (1700 < position < 2300)
        {
                motors.setSpeeds(speed1, speed1);
        }

        // Høyre

        if (position > 1700)
        {
                motors.setSpeeds(speed1 * 1.5, speed1 * 0.5);
        }

        if (position > 1500)
        {
                motors.setSpeeds(speed1 * 2, speed1 * 0.25);
        }

        // Venstre

        if (position < 2300)
        {
                motors.setSpeeds(speed1 * 0.5, speed1 * 1.5);
        }

        if (position < 2500)
        {
                motors.setSpeeds(speed1 * 0.25, speed1 * 2);
        }



        // Serial.println(position);
}

void loop()
{
        RUN();
        OLED();
        lenght();
}