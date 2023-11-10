#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);


const int powerButton = 2;
const int modeButton = 3;
int analog1 = A0;
int analog2 = A1;
int analog3 = A2;

int analogVal1 = 0;
int analogVal2 = 0;

int buttonCount1 = 0;
int buttonState1 = 0; 
int lastButtonState1 = 0;

int buttonCount2 = 0;
int buttonState2 = 0; 
int lastButtonState2 = 0;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;

const long interval = 750;// timing delay in milliseconds

const long interval_button = 100;// timing delay in milliseconds

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  // Initialize the NeoPixel library.
  Serial.begin(9600);
  u8g2.begin();
  u8g2.enableUTF8Print();

  pinMode(analog1, INPUT);
  pinMode(analog2, INPUT);
  pinMode(analog3, INPUT);

  pinMode(powerButton, INPUT);
  pinMode(modeButton, INPUT);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MODE 1
void mode1() {
  unsigned long currentMillis1 = millis();
   	  if (currentMillis1 - previousMillis1 >= interval) {	
          u8g2.firstPage();
      do {
          u8g2.setFont(u8g2_font_ncenB14_tr);
          u8g2.drawStr(0,30,"Kristian.G.");
       } 
       while ( u8g2.nextPage() );
          previousMillis1 = currentMillis1;
       }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MODE 2 Photoresistor
void mode2() {
  analogVal1 = map(analogRead(analog1),0,1024,0,100);
  unsigned long currentMillis2 = millis();
   	  if (currentMillis2 - previousMillis2 >= interval) {
   		    u8g2.firstPage();
      do {
          u8g2.setCursor(2, 20);
          u8g2.print("Photores'");
          u8g2.setCursor(50, 40);
          u8g2.print(analogVal1);
      } 
      while ( u8g2.nextPage() );
          previousMillis2 = currentMillis2;
      }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MODE 3 Thermoresistor
void mode3() {
  analogVal2 = map(analogRead(analog2),0,1024,0,100);
  unsigned long currentMillis3 = millis();
   	  if (currentMillis3 - previousMillis3 >= interval) {		
          u8g2.firstPage();
      do {
          u8g2.setCursor(2, 20);
          u8g2.print("Thermores'");
          u8g2.setCursor(50, 40);
          u8g2.print(analogVal2);
      } 
      while ( u8g2.nextPage() );
          previousMillis3 = currentMillis3;
      }
             	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MODE 4
void mode4() {
  unsigned long currentMillis4 = millis();
   	  if (currentMillis4 - previousMillis4 >= interval) {	
          u8g2.firstPage();
      do {
          u8g2.setFont(u8g2_font_ncenB14_tr);
          u8g2.drawStr(0,30," ");
       } 
       while ( u8g2.nextPage() );
          previousMillis4 = currentMillis4;
       }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Selects which mode to run
void OledFunc()
{
	   if (buttonCount1 == 1){
          mode1();
          }
          
      if (buttonCount1 == 2){
          mode2();
          }
  
      if (buttonCount1 == 3){
          mode3();
          }

      if (buttonCount1 == 0){
          mode4();
          }
         
}      
        
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funksjon for virkemåten til modus knapp
void buttonFunc1(){

  buttonState1 = digitalRead(modeButton);
  
  if (buttonState1 != lastButtonState1) {
    if (buttonState1 == HIGH) {
      buttonCount1++;
      
      Serial.print("number of button1 pushes: ");
      Serial.println(buttonCount1);
    } else {
      
    }
    delay(50);
  }
  lastButtonState1 = buttonState1;
  
    
   if (buttonCount1 > 3){
    
    buttonCount1 = 0;
  }
  

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funksjon for virkemåten til AV/PÅ knapp
void buttonFunc2(){
  buttonState2 = digitalRead(powerButton);
  
  if (buttonState2 != lastButtonState2) {
    if (buttonState2 == HIGH) {
      buttonCount2++;
      
      Serial.print("number of button2 pushes: ");
      Serial.println(buttonCount2);
    } else {
      
    }
    delay(50);
  }
  lastButtonState2 = buttonState2;
  
   if (buttonCount2 > 1){
    Serial.println("power off");
    buttonCount2 = 0;
   }
     
    if(buttonCount2 != 1){ 
      buttonCount1 = 0;
    }
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MAIN LOOP
void loop()
{
  OledFunc();
  buttonFunc1();
  buttonFunc2();
}
