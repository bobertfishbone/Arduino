#include <Wire.h>

#include <LiquidCrystal.h>

#define homebutton 16
#define menubutton 17
#define leftbutton 18
#define rightbutton 19
#define upbutton 20
#define downbutton 21

#define buttonup A6
#define buttondown A5
#define buttonselect A7

#define RS 46
#define enable 47
#define D4 42
#define D5 43
#define D6 44
#define D7 45



int numSteps = 0;
int hours = 0;
 int minutes = 0;

int myTemp[10];
long stageDuration[10];

long startTime;
long stageStart;

LiquidCrystal lcd(RS, enable, D4, D5, D6, D7);

void setup() {
  lcd.begin(16,2);
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

lcd.clear();
lcd.setCursor(0,0);
lcd.print("How many stages?");
numSteps = getNumber(1);

for (int i = 1; i <= numSteps; i++) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Setpoint for stg ");
  lcd.print(i);
  myTemp[i] = getNumber(3);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Duration (mins) for stg ");
  lcd.print(i);
  stageDuration[i] = getNumber(3) * 20000;
}

startTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
for (int i = 1; i <= numSteps; i++) {
  stageStart = millis();
  Serial.print("Starting stage ");
  Serial.println(i);
  Serial.print("Temp ");
  Serial.print(myTemp[i]);
  Serial.print("   Duration ");
  Serial.println(stageDuration[i]);
  
  if (i > 1) {
      lcd.clear();
  lcd.setCursor(0,0);
    lcd.print("Changing by ");
    lcd.print(myTemp[i] - myTemp[i-1]);
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
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("DONE");
}

void changeSetPoint(int degrees){
  Serial.println("Pushing menu");
  pushButton(menubutton, 1);
  Serial.println("Pushing right");
    pushButton(rightbutton, 1);
    
    if (degrees > 0){
      Serial.println("Pushing up");
  pushButton(upbutton, degrees);
    }
    else {
      Serial.println("Pushing down");
      pushButton(downbutton, degrees*-1);
      }
  goHome();
}

void goHome() {
  Serial.println("GOING HOME");
  pushButton(homebutton, 1);
}

void pushButton(int button, int times){
  for (int i = 1; i<=times; i++){
  long time1 = millis();
  Serial.println("PUSH!");
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
  lcd.setCursor(0,0);
  for (int i = digits; i >= 1; i--)
  {
    
    while (digitalRead(buttonselect) == HIGH) {
      //Serial.println("BUTTONSELECT IS HIGH");
      if (digitalRead(buttonup) == LOW) {
        //Serial.println("BUTTONUP IS LOW!");
        digit[i]++;
        if (digit[i] < 0) {
          digit[i] = 9;
        }
        else if (digit[i] > 9) {
          digit[i] = 0;
        }
        lcd.setCursor(i, 1);
        lcd.print(digit[i]);
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
  Serial.println(digit[1]);
  Serial.println(digit[2]);
  Serial.println(digit[3]);
  
  int returnval = (digit[1]*100) + (digit[2] * 10) + digit[3];
  //Serial.print("RETURNIN!!! ");
  Serial.println(returnval);
  return returnval;
}

