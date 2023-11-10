int greenLed = 13;
int yellowLed = 12;
int blueLed = 11;
int button = 10;

unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;

const long interval = 850; // timing delay in milliseconds
const long interval_button = 50; // timing delay in milliseconds
const long timer_button = 2000; // timing delay in milliseconds


int buttonCounter = 0;
int buttonCounter2 = 0;

int ledstate = LOW;
int ledstate1 = LOW;
int ledstate2 = LOW;
int buttonState = digitalRead(button);
int buttonState2 = digitalRead(button);
int lastButtonState = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(button, INPUT);
}

////////////////////////////////////////////////////////////////////////////////////

void button_func1()
{
  buttonState = digitalRead(button);
  
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonCounter++;
      
      Serial.print("number of button1 pushes: ");
      Serial.print(buttonCounter);
    } else {
      
    }
    delay(50);
  }
  lastButtonState = buttonState;
  
    
   if (buttonCounter > 1){
    
    buttonCounter = 0;
  }
  

}

////////////////////////////////////////////////////////////////////////////////////

void button_func2()
{
if (buttonState2 == HIGH){
  unsigned long currentMillis3 = millis();
  if (currentMillis3 - previousMillis3 >= timer_button)
  {
    buttonCounter2++;
    previousMillis3 = currentMillis3;
  }
}
if (buttonCounter2 > 2){
  buttonCounter2 = 0;
}
}

////////////////////////////////////////////////////////////////////////////////////

void mode_select()
{
if (buttonCounter2 == 0)
{
  button_func1();
  shift_light();
}
else if (buttonCounter2 == 1)
{
  blink_func1();
}
else if (buttonCounter2 == 2)
{
  blink_func2();
}
}

////////////////////////////////////////////////////////////////////////////////////

void blink_func()
{

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    ledstate = !ledstate;
    digitalWrite(yellowLed, ledstate);
    previousMillis = currentMillis;
  }

  
}

////////////////////////////////////////////////////////////////////////////////////

void blink_func1()
{

  unsigned long currentMillis1 = millis();
  if (currentMillis1 - previousMillis1 >= interval)
  {
    ledstate1 = !ledstate1;
    digitalWrite(greenLed, ledstate1);
    previousMillis1 = currentMillis1;
  }

  
}

////////////////////////////////////////////////////////////////////////////////////

void blink_func2()
{

  unsigned long currentMillis2 = millis();
  if (currentMillis2 - previousMillis2 >= interval)
  {
    ledstate2 = !ledstate2;
    digitalWrite(blueLed, ledstate2);
    previousMillis2 = currentMillis2;
  }

  
}

////////////////////////////////////////////////////////////////////////////////////

void shift_light()
{
  if (buttonCounter == 0)
  {
    digitalWrite(greenLed, HIGH);
    digitalWrite(blueLed, LOW);
  }
  else if (buttonCounter == 1)
  {
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, HIGH);
  }
}

////////////////////////////////////////////////////////////////////////////////////

void loop()
{
  button_func2();
  mode_select();
  blink_func();
  Serial.println(buttonState2);
}