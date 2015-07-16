#define homebutton 2
#define menubutton 3
#define leftbutton 4
#define rightbutton 5
#define upbutton 6
#define downbutton 7

#define buttonup 8
#define buttondown 9
#define buttonselect 10

unsigned int numSteps = 0;
unsigned int hours = 0;
unsigned int minutes = 0;

unsigned int myTemp[10];
long stageDuration[10];

long startTime;
long stageStart;


void setup() {
Serial.begin(9600);

pinMode(homebutton, OUTPUT);
pinMode(menubutton, OUTPUT);
pinMode(leftbutton, OUTPUT);
pinMode(rightbutton, OUTPUT);
pinMode(upbutton, OUTPUT);
pinMode(downbutton, OUTPUT);

pinMode(buttonup, INPUT_PULLUP);
pinMode(buttondown, INPUT_PULLUP);
pinMode(buttonselect, INPUT_PULLUP);

digitalWrite(homebutton, LOW);
digitalWrite(menubutton, LOW);
digitalWrite(leftbutton, LOW);
digitalWrite(rightbutton, LOW);
digitalWrite(upbutton, LOW);
digitalWrite(downbutton, LOW);

Serial.println("How many stages?");
numSteps = getNumber(1);

for (int i = 1; i <= numSteps; i++) {
  Serial.print("Setpoint for stg ");
  Serial.println(i);
  myTemp[i] = getNumber(3);

  Serial.print("Duration (mins) for stg ");
  Serial.println(i);
  stageDuration[i] = getNumber(3) * 60000;
}

startTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
for (int i = 0; i < numSteps; i++) {
  stageStart = millis();

  if (i > 0) {
    changeSetPoint(myTemp[i] - myTemp[i-1]);
    }

  while ((millis() - stageStart) < stageDuration[i])
  {
    bool spaceHog = true;
  }
}
digitalWrite(homebutton, HIGH);
digitalWrite(menubutton, HIGH);
digitalWrite(leftbutton, HIGH);
digitalWrite(rightbutton, HIGH);
digitalWrite(upbutton, HIGH);
digitalWrite(downbutton, HIGH);
delay(9999999999999999999999);
}

void changeSetPoint(int degrees){
  pushButton(menubutton, 1);
  Serial.println("Pushing menu");
    pushButton(rightbutton, 1);
    Serial.println("Pushing right");
    if (degrees > 0){
  pushButton(upbutton, degrees);
    }
    else pushButton(downbutton, degrees);
  Serial.println("Pushing up/down");
  goHome();
}

void goHome() {
  pushButton(homebutton, 1);
}

void pushButton(int button, int times){
  for (int i = 1; i<=times; i++){
  long time1 = millis();
  while(millis() < time1+250){
  digitalWrite(button, HIGH);
  }
  while (millis() < time1+500){
    digitalWrite(button, LOW);
  }
  }
}

int getNumber(int digits) {
  int digit[3] = {0, 0, 0};
  Serial.print(digit[1]);
  Serial.print(digit[2]);
  Serial.println(digit[3]);

  for (int i = digits; i >= 1; i--)
  {
    Serial.println("I'M IN THE FOR LOOP NOW");
    while (digitalRead(buttonselect) == HIGH) {
      //Serial.println("BUTTONSELECT IS HIGH");
      if (digitalRead(buttonup) == LOW) {
        Serial.println("BUTTONUP IS LOW!");
        digit[i]++;
        Serial.print(digit[i]);
        delay(250);
      }
      /*else if (digitalRead(buttondown) == HIGH) {
        digit[i]--;
        Serial.print(digit[i]);
        delay(150);
      }*/
    }
    delay(250);
  }
  int returnval = (digit[3]*100) + (digit[2] * 10) + digit[1];
  Serial.print("RETURNIN!!! ");
  Serial.println(returnval);
  return returnval;
}

