#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo

int analogPin0 = A0; 
int analogPin1 = A1;
int analogPin2 = A2;
int analogPin3 = A3;
int analogPin4 = A4;
int analogPin5 = A5; 

int servoVal0;   
int servoVal1;

int sensVal2;
int sensVal3;
int sensVal4;
int sensVal5;

unsigned long currentMillis0 = 0;
unsigned long currentMillis1 = 0;
unsigned long currentMillis2 = 0;
unsigned long currentMillis3 = 0;

unsigned long lastMillis0 = 0;
unsigned long lastMillis1 = 0;
unsigned long lastMillis2 = 0;
unsigned long lastMillis3 = 0;

int interval0 = 15;

void setup() {
    myservo1.attach(9);      
    myservo2.attach(10);  

    pinMode(analogPin2,INPUT);
    pinMode(analogPin3,INPUT);
    pinMode(analogPin4,INPUT);
    pinMode(analogPin5,INPUT);
    
}


void styring(){

    sensVal2 = analogRead(analogPin2);
    sensVal3 = analogRead(analogPin3);
    sensVal4 = analogRead(analogPin4);
    sensVal5 = analogRead(analogPin5);

    if ((sensVal2 + sensVal3) > (sensVal4 + sensVal5)){
        
    }
}
    



void servo1() {
  currentMillis0 = millis();

    if (currentMillis0 - lastMillis0 > interval0){
        currentMillis0 = lastMillis0;
        servoVal0 = analogRead(analogPin0);              
        servoVal0 = map(servoVal0, 0, 1023, 0, 180);     
        myservo1.write(servoVal0);                                     
}
}

void servo2() {
    currentMillis1 = millis();

    if (currentMillis1 - lastMillis1 > interval0){
        currentMillis1 = lastMillis1;
        servoVal1 = analogRead(analogPin1);            
        servoVal1 = map(servoVal1, 0, 1023, 0, 180);     
        myservo2.write(servoVal1);                  
                          
}
}

void loop(){
servo1();
servo2();
}