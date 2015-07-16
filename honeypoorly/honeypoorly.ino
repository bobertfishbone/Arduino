#include <ShiftRegLCD123.h>

#include <Wire.h>

#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR_LCD3.h>

#define home 2
#define menu 3
#define left 4
#define right 5
#define up 6
#define down 7

#define buttonup 0
//#define buttondown 1
#define buttonselect 11

int numSteps = 0;
int hours = 0;
int minutes = 0;

int myTemp[10];
unsigned long stageDuration[10];

unsigned long startTime;
unsigned long stageStart;

LiquidCrystal_SR_LCD3 lcd(8, 9, 10);

void setup() {

Serial.begin(9600);
Serial.println("I'M HERE");
lcd.begin(16, 2);


pinMode(buttonup, INPUT_PULLUP);
//pinMode(buttondown, INPUT_PULLUP);
pinMode(buttonselect, INPUT_PULLUP);

pinMode(home, OUTPUT);
pinMode(menu, OUTPUT);
pinMode(left, OUTPUT);
pinMode(right, OUTPUT);
pinMode(up, OUTPUT);
pinMode(down, OUTPUT);

digitalWrite(home, LOW);
digitalWrite(menu, LOW);
digitalWrite(left, LOW);
digitalWrite(right, LOW);
digitalWrite(up, LOW);
digitalWrite(down, LOW);

Serial.println("STAGES");
//Serial.setCursor(0, 0);
Serial.println("How many stages?");

numSteps = getNumber(1);
//numSteps = 9;

for (int i=1; i <= numSteps; i++){
  lcd.clear();
  lcd.setCursor(0,0);
  Serial.print(F("Setpoint for stg "));
  Serial.println(i);
  myTemp[i] = getNumber(3);
  //myTemp[i] = i*3*2;
  Serial.print(F("Duration for stg "));
  Serial.println(i);
  stageDuration[i] = getNumber(2)*1000;
  
}

startTime = millis();

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print("Starting cycle!");
  Serial.println(F("Starting cycle"));
for (int i = 1; i <= numSteps; i++) {
  stageStart = millis();

  if (i > 1) {
    changeSetPoint(myTemp[i] - myTemp[i-1]);
  }
  
  while (millis() - stageStart < stageDuration[i])
  {
    bool spaceHog = true;
  }

  
}
digitalWrite(home, HIGH);
digitalWrite(menu, HIGH);
digitalWrite(left, HIGH);
digitalWrite(right, HIGH);
digitalWrite(up, HIGH);
digitalWrite(down, HIGH);


  

}

void changeSetPoint(int degrees){
  pushButton(menu, 1);
  Serial.println("Pushing menu");
    pushButton(right, 1);
    Serial.println("Pushing right");
    if (degrees > 0){
  pushButton(up, degrees);
    }
    else pushButton(down, degrees);
  Serial.println("Pushing up/down");
  goHome();
}

void goHome()
{
  pushButton(home, 1);
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

unsigned int getNumber(unsigned int digits) {
  Serial.println("GETNUMBER");
int digit[3] = {0, 0, 0};
lcd.setCursor(0,1);
lcd.print(digit[1]);
lcd.print(digit[2]);
lcd.print(digit[3]);

for (int i = digits; i > 1 ; i--){
lcd.setCursor(0,i);
while(buttonselect == LOW) {
 if (buttonup == HIGH) {
  digit[i]++;
  lcd.setCursor(0, i);
  lcd.print(digit[i]);
  delay(150);
  }
 /*else if (buttondown == LOW) {
  digit[i]--;
  lcd.setCursor(0, i);
  lcd.print(digit[i]);
  delay(150);
 }*/
}
delay(150);
}
unsigned int returnval = (digit[1]*100) + (digit[2] * 10) + digit[3];
return returnval;
Serial.println(returnval);
}


