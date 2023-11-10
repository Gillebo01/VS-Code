

//const char label1 = 'R';
//const char label2 = 'G';
//const char label3 = 'B';

int Red = 12;
int Green = 8;
int Blue = 5;

char var = 0;

bool redState = LOW;
bool greenState = LOW;
bool blueState = LOW;

///////////////////////////////////////////////////

void setup(){
Serial.begin(9600);
pinMode(Red, OUTPUT);
pinMode(Green, OUTPUT);
pinMode(Blue, OUTPUT);
//hey();
}

///////////////////////////////////////////////////

//void hey(){

//}

///////////////////////////////////////////////////

void lysStyring(){
if (Serial.available() > 0) {
    // read the incoming byte:
    var = toUpperCase(Serial.read());


switch (var){

case('R'):
redState = !redState;
digitalWrite(Red,redState);
break;

case('G'):
greenState = !greenState;
digitalWrite(Green,greenState);
break;

case('B'):
blueState = !blueState;
digitalWrite(Blue,blueState);
break;
}
//case('r'):
//digitalWrite(Red,LOW);
//break;

//case('g'):
//digitalWrite(Green,LOW);
//break;

//case('b'):
//digitalWrite(Blue,LOW);
//break;

}

}

///////////////////////////////////////////////////

void loop(){
lysStyring();
}
