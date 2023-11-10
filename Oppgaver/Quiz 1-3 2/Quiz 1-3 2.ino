

int led = 8;

int lightMode1 = 0;
int lightMode2 = 0;

int sum = 0;

int anVal1 = A1;

const long interval1 = 1000; // timing delay in milliseconds
const long interval2 = 166;  // timing delay in milliseconds
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(led, OUTPUT);
    pinMode(anVal1, INPUT);
}

int gjennomsnitt()
{

    int lastFiveNums[] = {0};
    int currentIndex = 0;

    for (int i = 0; i <= 4; i++)
    {

        if (lastFiveNums[i] != 0)
        {
            sum += lastFiveNums[i];
            sum -= lastFiveNums[i - 5];
        }

        int anVal = map(analogRead(anVal1), 0, 1023, 0, 200);
        lastFiveNums[currentIndex] = anVal;
        currentIndex++;

        if (currentIndex == 4)
        {
            currentIndex = 0;
        }

        //   [0,0,0,0,0]
    }

    return sum / 4;
}


void blink()
{

    if (gjennomsnitt() > 100)
    {
        unsigned long currentMillis1 = millis();
        if (currentMillis1 - previousMillis1 >= interval1)
        {
            lightMode1 = lightMode1 + 1;
            previousMillis1 = currentMillis1;

            if (lightMode1 == 1)
            {
                digitalWrite(led, HIGH);
            }

            if (lightMode1 == 2)
            {
                digitalWrite(led, LOW);
                lightMode1 = 0;
            }
        }
    }

    if (gjennomsnitt() < 100)
    {
        unsigned long currentMillis2 = millis();
        if (currentMillis2 - previousMillis2 >= interval2)
        {
            lightMode2 = lightMode2 + 1;
            previousMillis2 = currentMillis2;

            if (lightMode2 == 1)
            {
                digitalWrite(led, HIGH);
            }

            if (lightMode2 == 2)
            {
                digitalWrite(led, LOW);
                lightMode2 = 0;
            }
        }
    }
}

void loop()
{
    blink();
    Serial.println(gjennomsnitt());
}