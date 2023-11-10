/*If a motor on your Zumo has been flipped, you can correct its
direction by uncommenting the call to flipLeftMotor() or
flipRightMotor() in the setup() function. */

#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Encoders encoders;
Zumo32U4Buzzer buzzer;
Zumo32U4OLED display;
const char encoderErrorLeft[] PROGMEM = "!<c2";
const char encoderErrorRight[] PROGMEM = "!<e2";
char report[80];

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;
unsigned long previousMillis5 = 0;

int start1 = 0;
int start2 = 0;
int start3 = 0;
int start4 = 0;
int start5 = 0;

const long interval1 = 2;   // timing delay in milliseconds
const long interval2 = 2000; // timing delay in milliseconds

void setup()
{
    // Wait for the user to press button A.
    buttonA.waitForButton();
    Serial.begin(9600);

    // Delay so that the robot does not move away while the user is
    // still touching it.
    delay(1000);
}

void runForward()
{
    unsigned long currentMillis1 = millis();
    if (currentMillis1 - previousMillis1 >= interval1)
    {
        start1 = start1 + 1;

        if (start1 == 1)
        {
            for (int speed = 0; speed <= 100; speed++)
            {
                ledYellow(1);
                motors.setLeftSpeed(speed);
                motors.setRightSpeed(speed);
            }
        }

        else if (start1 == 2)
        {
            for (int speed = 100; speed >= 0; speed--)
            {
                motors.setLeftSpeed(speed);
                motors.setRightSpeed(speed);
                start1 == 0;
            }
        }
        currentMillis1 = previousMillis1;
    }
}

void turnLeft()
{
    unsigned long currentMillis2 = millis();
    if (currentMillis2 - previousMillis2 >= interval1)
    {
        start2 = start2 + 1;

        if (start2 == 1)
        {
            ledYellow(0);
            for (int speed = 0; speed >= -100; speed--)
            {
                motors.setRightSpeed(speed);
                motors.setLeftSpeed(-speed);
            }
        }

        else if (start2 == 2)
        {
            for (int speed = -100; speed <= 0; speed++)
            {
                motors.setRightSpeed(speed);
                motors.setLeftSpeed(-speed);
                start2 = 0;
            }
        }
        currentMillis2 = previousMillis2;
    }
}

void turnRight()
{
    unsigned long currentMillis3 = millis();
    if (currentMillis3 - previousMillis3 >= interval1)
    {
        start3 = start3 + 1;

        if (start3 == 1)
        {
            ledYellow(0);
            for (int speed = 0; speed >= -100; speed--)
            {
                motors.setRightSpeed(-speed);
                motors.setLeftSpeed(speed);
            }
        }

        else if (start3 == 2)
        {
            for (int speed = -100; speed <= 0; speed++)
            {
                motors.setRightSpeed(-speed);
                motors.setLeftSpeed(speed);
                start3 = 0;
            }
        }
        currentMillis3 = previousMillis3;
    }
}

void turnAround()
{
    unsigned long currentMillis4 = millis();
    if (currentMillis4 - previousMillis4 >= interval1)
    {
        start4 = start4 + 1;

        if (start4 == 1)
        {
            ledYellow(0);
            for (int speed = 0; speed >= -150; speed--)
            {
                motors.setRightSpeed(speed);
                motors.setLeftSpeed(-speed);
            }
        }

        else if (start4 == 2)

        {
            for (int speed = -150; speed <= 0; speed++)
            {
                motors.setRightSpeed(speed);
                motors.setLeftSpeed(-speed);
                start4 = 0;
            }
        }
        currentMillis4 = previousMillis4;
    }
}

void oledDisplay()
{
    static uint8_t lastDisplayTime;
    static uint8_t displayErrorLeftCountdown = 0;
    static uint8_t displayErrorRightCountdown = 0;

    if ((uint8_t)(millis() - lastDisplayTime) >= 100)
    {
        lastDisplayTime = millis();

        int16_t countsLeft = encoders.getCountsLeft();
        int16_t countsRight = encoders.getCountsRight();

        bool errorLeft = encoders.checkErrorLeft();
        bool errorRight = encoders.checkErrorRight();

        if (errorLeft)
        {
            // An error occurred on the left encoder channel.
            // Show it on the display for the next 10 iterations and
            // also beep.
            displayErrorLeftCountdown = 10;
            buzzer.playFromProgramSpace(encoderErrorLeft);
        }

        if (errorRight)
        {
            // An error occurred on the right encoder channel.
            // Show it on the display for the next 10 iterations and
            // also beep.
            displayErrorRightCountdown = 10;
            buzzer.playFromProgramSpace(encoderErrorRight);
        }

        // Update the display with encoder counts and error info.
        display.clear();
        display.print(countsLeft);
        display.gotoXY(0, 1);
        display.print(countsRight);

        if (displayErrorLeftCountdown)
        {
            // Show an exclamation point on the first line to
            // indicate an error from the left encoder.
            display.gotoXY(7, 0);
            display.print('!');
            displayErrorLeftCountdown--;
        }

        if (displayErrorRightCountdown)
        {
            // Show an exclamation point on the second line to
            // indicate an error from the left encoder.
            display.gotoXY(7, 1);
            display.print('!');
            displayErrorRightCountdown--;
        }

        // Send the information to the serial monitor also.
        snprintf_P(report, sizeof(report),
                   PSTR("%6d %6d %1d %1d"),
                   countsLeft, countsRight, errorLeft, errorRight);
        Serial.println(report);
    }
}

void RUN()
{
    unsigned long currentMillis5 = millis();
    if (currentMillis5 - previousMillis5 >= interval2)
    {
        start5 = start5 + 1;

        if (start5 == 1)
        {
            runForward();
        }

        else if (start5 == 2)
        {
            turnLeft();
        }

        else if (start5 == 3)
        {
            turnAround();
        }

        else if (start5 == 4)
        {
            runForward();
        }

        else if (start5 == 5)
        {
            turnRight();
        }

        else if (start5 == 6)
        {
            runForward();
            start5 = 0;
        }

        
        currentMillis5 = previousMillis5;
    }
}

void loop()
{
    RUN();
    oledDisplay();
}