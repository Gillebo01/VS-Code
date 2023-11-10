/*If a motor on your Zumo has been flipped, you can correct its
direction by uncommenting the call to flipLeftMotor() or
flipRightMotor() in the setup() function. */

#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;

void setup()
{
  // Uncomment if necessary to correct motor directions:
  // motors.flipLeftMotor(true);
  // motors.flipRightMotor(true);

  // Wait for the user to press button A.
  buttonA.waitForButton();
  Serial.begin(9600);

  // Delay so that the robot does not move away while the user is
  // still touching it.
  delay(1000);
}

void runForward()
{
  ledYellow(1);
  for (int speed = 0; speed <= 200; speed++)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
  for (int speed = 200; speed >= 0; speed--)
  {
    motors.setLeftSpeed(speed);
    motors.setRightSpeed(speed);
    delay(2);
  }
}

void turnLeft()
{
  ledYellow(0);
  for (int speed = 0; speed >= -200; speed--)
  {
    motors.setRightSpeed(speed);
    motors.setLeftSpeed(-speed);
    delay(2);
  }
  for (int speed = -200; speed <= 0; speed++)
  {
    motors.setRightSpeed(speed);
    motors.setLeftSpeed(-speed);
    delay(2);
  }
}

void turnRight()
{
  ledYellow(0);
  for (int speed = 0; speed >= -200; speed--)
  {
    motors.setRightSpeed(-speed);
    motors.setLeftSpeed(speed);
    delay(2);
  }
  for (int speed = -200; speed <= 0; speed++)
  {
    motors.setRightSpeed(-speed);
    motors.setLeftSpeed(speed);
    delay(2);
  }
}

void turnAround()
{
  ledYellow(0);
  for (int speed = 0; speed >= -350; speed--)
  {
    motors.setRightSpeed(speed);
    motors.setLeftSpeed(-speed);
    delay(2);
  }
  for (int speed = -350; speed <= 0; speed++)
  {
    motors.setRightSpeed(speed);
    motors.setLeftSpeed(-speed);
    delay(2);
  }
}

void RUN()
{
  runForward();
  delay(2);
  turnLeft();
  delay(2);
  turnAround();
  delay(2);
  runForward();
  delay(2);
  turnRight();
  delay(2);
  runForward();
  delay(500);
}

void loop()
{
  RUN();
}