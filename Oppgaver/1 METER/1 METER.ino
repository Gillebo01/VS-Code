/*If a motor on your Zumo has been flipped, you can correct its
direction by uncommenting the call to flipLeftMotor() or
flipRightMotor() in the setup() function. */

#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Encoders encoders;
Zumo32U4Buzzer buzzer;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
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



char report[80];

void setup()
{
    // Uncomment if necessary to correct motor directions:
    // motors.flipLeftMotor(true);
    // motors.flipRightMotor(true);

    // Wait for the user to press button A.
    buttonA.waitForButton();
    Serial.begin(9600);
    delay(10);
}

// if (1800 < position < 2200){motor.setSpeed(100.100)}

void oneMeter()
{

    speed();
    lenght();

    static uint8_t lastDisplayTime;
    static uint8_t displayErrorLeftCountdown = 0;
    static uint8_t displayErrorRightCountdown = 0;

    if ((uint8_t)(millis() - lastDisplayTime) >= 100)
    {
        lastDisplayTime = millis();

        display.clear();
        display.print(travel);
        // display.print(countsLeft);
        // display.gotoXY(0, 1);
        // display.print(countsRight);
        display.gotoXY(5, 0);
        display.print(motorSpeed);

        if (travel < 2000)
        {
            motors.setSpeeds(140, 80);
        }
        else
        {
            motors.setSpeeds(0, 0);
        }
    }
}



void speed()
{

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

void battery()
{
}

void loop()
{
    oneMeter();
    
}