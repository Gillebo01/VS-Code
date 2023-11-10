#include <Adafruit_NeoPixel.h>



#define PIN 10	 // input pin Neopixel is attached to

#define NUMPIXELS     32 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
 

int red = 0;
int green = 0;
int blue = 0;

int lightMode1 = 0;
int lightMode2 = 0;
int lightMode3 = 0;

int currentLed = 0;
int way_turn = 0;
const int powerButton = 2;
const int modeButton = 3;
int analog = A0;

int buttonCount1 = 0;
int buttonState1 = 0; 
int lastButtonState1 = 0;

int buttonCount2 = 0;
int buttonState2 = 0; 
int lastButtonState2 = 0;

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;

const long interval = 50;// timing delay in milliseconds
const long interval_button = 100;// timing delay in milliseconds

int delay_time = 20;


void setup() {
  // Initialize the NeoPixel library.
  pixels.begin();
  Serial.begin(9600);
  
  pinMode(analog, INPUT);

  pinMode(powerButton, INPUT);
  pinMode(modeButton, INPUT);
}





// MODE 1
void mode1() {

while (currentLed < 31){
unsigned long currentMillis1 = millis();
   	  if (currentMillis1 - previousMillis1 >= interval) {
   	  // from left to right
      for(int currentLed=0; currentLed<NUMPIXELS; currentLed++){
        pixels.setPixelColor(currentLed, red, 0, 0);
        pixels.show();
  		  previousMillis1 = currentMillis1; 
        pixels.setPixelColor(currentLed, 0, 0, 0);
        pixels.show();
		    }
      }
    }

while (currentLed > 0){
unsigned long currentMillis2 = millis();
      if (currentMillis2 - previousMillis2 >= interval) {
      // from right to left
      for(int currentLed=NUMPIXELS; currentLed>0; currentLed--){
        pixels.setPixelColor(currentLed, red, 0, 0);
        pixels.show();
        previousMillis2 = currentMillis2;
        pixels.setPixelColor(currentLed, 0, 0, 0);
        pixels.show();
        }
      }
    }  
}









// MODE 2
void mode2() {
  
unsigned long currentMillis2 = millis();
   	   if (currentMillis2 - previousMillis2 >= interval) {
   		lightMode2 = lightMode2 +1;
  		previousMillis2 = currentMillis2;
		}
  
       if (lightMode2 == 1){
        setColorYellow();
       
  		for (int i=0; i < NUMPIXELS; i=i+2) {
    	pixels.setPixelColor(i, pixels.Color(red, green, blue)); // Brukes for å velge hvilke led som skal lyse [i]
      	pixels.show();
        }
       }
          
          
          
      if (lightMode2 == 2){
        setColorPurple();
        
        for (int i=1; i < NUMPIXELS; i=i+2) {
        pixels.setPixelColor(i, pixels.Color(red, green, blue)); 
        pixels.show();
        }
       }
          
      if (lightMode2 == 3){
        setColorBrown();
        
        for (int i=0; i < NUMPIXELS; i=i+2) {
        pixels.setPixelColor(i, pixels.Color(red, green, blue)); 
        pixels.show();
        }
       }
  
  
  
      if (lightMode2 == 4){
            setColorBlue();

        for (int i=1; i < NUMPIXELS; i=i+2) {
        pixels.setPixelColor(i, pixels.Color(red, green, blue)); 
        pixels.show();
        lightMode2 = 0;
        }
       }    	
}



// MODE 3
void mode3() {

unsigned long currentMillis3 = millis();
   	if (currentMillis3 - previousMillis3 >= analogRead(analog)) {
   		lightMode3 = lightMode3 +1;
  		previousMillis3 = currentMillis3;
		}
  
    if (lightMode3 == 1){
      setColorRandom();
       
  	for (int i=0; i < NUMPIXELS; i++) {
    	pixels.setPixelColor(i, pixels.Color(red, green, blue)); // Brukes for å velge hvilke led som skal lyse [i]
      pixels.show();
      lightMode3 = 0;
      }
    } 
             	
}


// MODE 4
void mode4(){
  setColorOff();
  for (int i=0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(red, green, blue)); 
        pixels.show();
        }
}






// setColor()
// picks values to set for RGB
void setColorRed(){
  red = (255);
  green = (0);
  blue = (0);
}

void setColorGreen(){
  red =   (0);
  green = (255);
  blue =  (0);
}

void setColorBlue(){
  red =   (0);
  green = (0);
  blue =  (255);
}

void setColorBrown(){
  red =   (120);
  green = (55);
  blue =  (15);
}

void setColorPurple(){
  red =   (112);
  green = (48);
  blue =  (160);
}

void setColorYellow(){
  red =   (255);
  green = (255);
  blue =  (0);
}

void setColorRandom(){
  red =   random(0,255);
  green = random(0,255);
  blue =  random(0,255);
}

void setColorOff(){
  red =   (0);
  green = (0);
  blue =  (0);
}






// Selects which mode to run
void ledFunc()
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







// MAIN LOOP
void loop()
{
  ledFunc();
  buttonFunc1();
  buttonFunc2();
}