//  Hva gjør denne koden?
//  1. Analyser  2. Kommenter  3. Skriv funksjonalitetskrav

int redLED = 10;
int greenLED = 9;
int buzzerPin = 11;

int LED1 = 6;
int LED2 = 7;
int SW1 = 3;
int SW2 = 4;

int winner = 0;
int winnerBeep = 750;
int fault = 0;
int faultBeep = 200;

unsigned long wait = 0;
unsigned long now = 0;

void setup()
{
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
}

void startValues()
{
  digitalWrite(redLED, HIGH);

  fault = 0;
  now = millis();
  wait = now + random(3000, 7000);
}

void game()
{
  startValues();

  while (millis() < wait && digitalRead(SW1) == HIGH && digitalRead(SW2) == HIGH)
  {
  }

  if (digitalRead(SW1) == LOW)
    fault = LED1;
  if (digitalRead(SW2) == LOW)
    fault = LED2;
  digitalWrite(redLED, LOW);

  if (fault == 0)
  {
    digitalWrite(greenLED, HIGH);
    while (digitalRead(SW1) == HIGH && digitalRead(SW2) == HIGH)
    {
    }
    if (digitalRead(SW1) == LOW)
    {
      winner = LED1;
    }
    else
    {
      winner = LED2;
    }

    for (int k = 0; k < 5; k++)
    {
      tone(buzzerPin, (winnerBeep + (k * 20)));
      digitalWrite(greenLED, HIGH);
      digitalWrite(winner, HIGH);
      delay(50);
      digitalWrite(winner, LOW);
      digitalWrite(greenLED, LOW);
      delay(50);
    }
    noTone(buzzerPin);
  }

  else
  {
    tone(buzzerPin, faultBeep, 500);
    for (int k = 0; k < 10; k++)
    {
      digitalWrite(redLED, HIGH);
      digitalWrite(fault, HIGH);
      delay(50);
      digitalWrite(redLED, LOW);
      digitalWrite(fault, LOW);
      delay(50);
    }
  }
}

void loop()
{
  game();
}
