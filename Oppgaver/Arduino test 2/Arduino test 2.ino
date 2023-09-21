const int buttonPin=2;

void setup()
{
    Serial.begin(9600);

    pinMode(buttonPin, INPUT);
}


void loop()
{

    Serial.println(digitalRead(buttonPin));
}