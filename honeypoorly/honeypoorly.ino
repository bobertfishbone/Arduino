#include <ShiftRegLCD123.h>

#define home 2
#define menu 3
#define left 4
#define right 5
#define up 6
#define down 7

#define buttonup 0
#define buttondown 1
#define buttonselect 11

byte numSteps = 0;
byte hours = 0;
byte minutes = 0;

byte myTemp[10];
unsigned long stageDuration[10];

unsigned long startTime;
unsigned long stageStart;

ShiftRegLCD123 lcd(8, 9, 10, SRLCD123);

void setup() {

lcd.begin(16, 2);

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

lcd.setCursor(0, 0);
lcd.print(F("How many stages?"));
numSteps = getNumber(1);

for (byte i=1; i <= numSteps; i++){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Setpoint for stg "));
  lcd.print(i);
  myTemp[i] = getNumber(3);
  
}

startTime = millis();

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(F("Starting cycle"));
for (byte i = 1; i < numSteps; i++) {
  stageStart = millis();

  if (i > 1) {
    changeSetPoint(myTemp[i] - myTemp[i-1]);
  }
  
  while (millis() - stageStart < stageDuration[i])
  {
    bool spaceHog = true;
  }

  
}



  

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
byte digit[3] = {0, 0, 0};
lcd.setCursor(0,1);
lcd.print(digit[1]);
lcd.print(digit[2]);
lcd.print(digit[3]);

for (byte i = digits; i > 1 ; i--){
lcd.setCursor(0,i);
while(buttonselect == HIGH) {
 if (buttonup == LOW) {
  digit[i]++;
  lcd.setCursor(0, i);
  lcd.print(digit[i]);
  delay(150);
  }
 else if (buttondown == HIGH) {
  digit[i]--;
  lcd.setCursor(0, i);
  lcd.print(digit[i]);
  delay(150);
 }
}
delay(150);
}
unsigned int returnval = (digit[1]*100) + (digit[2] * 10) + digit[3];
return returnval;
}


