#include <Wire.h>

#include <LiquidCrystal.h>

#define homebutton 24
#define menubutton 27
#define leftbutton 26
#define rightbutton 25
#define upbutton 23
#define downbutton 22

#define buttonup A6
#define buttondown A5
#define buttonselect A7

#define RS 46
#define enable 47
#define D4 42
#define D5 43
#define D6 44
#define D7 45


long numSteps = 0;
long initialtemp;
unsigned int hours = 0;
unsigned int minutes = 0;
bool stringcomplete = 0;
long myTemp[10];
long stageDuration[10];

long startTime;
long stageStart;

LiquidCrystal lcd(RS, enable, D4, D5, D6, D7);

void setup() {
  lcd.begin(16, 2);
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
  goHome();
  lcd.clear();
  lcd.setCursor(0, 0);
  Serial.println("What's the current temperature on the Honeywell?");
  pushButton(rightbutton, 1);
  initialtemp=getNumber(3);
  Serial.println("How many stages?");

  numSteps = getNumber(1);
  //numSteps = 5;

  for (int i = 1; i <= numSteps; i++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    Serial.print("Setpoint for stg ");
    Serial.println(i);
    myTemp[i] = getNumber(3);
    //myTemp[i] = 2*i;

    lcd.clear();
    lcd.setCursor(0, 0);
    Serial.print("Duration (mins) for stg ");
    Serial.println(i);
    stageDuration[i] = getNumber(3) * 60000;
    //stageDuration[i] = 20000;
  }
Serial.println("Initial calibration");
changeSetPoint(myTemp[1]-initialtemp);

  startTime = millis();
}

void loop() {
  goHome();
  // put your main code here, to run repeatedly:
  for (int i = 1; i <= numSteps; i++) {
    
    

    if (i > 1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      Serial.print("Changing by ");
      Serial.println(myTemp[i] - myTemp[i - 1]);
      changeSetPoint(myTemp[i] - myTemp[i - 1]);
    }

    lcd.clear();
    lcd.setCursor(0,0);
    Serial.print("Starting stage ");
    Serial.println(i);
    lcd.setCursor(0,1);
    Serial.print("Temp ");
    Serial.println(myTemp[i]);
    Serial.print("   Duration ");
    Serial.println(stageDuration[i]);
    stageStart = millis();
    while ((millis() - stageStart) < stageDuration[i])
    {
      lcd.setCursor(9,1);
      lcd.print((millis() - stageStart)/1000);
      lcd.print("/");
      lcd.print(stageDuration[i]/1000);
    }
  }
  digitalWrite(homebutton, LOW);
  digitalWrite(menubutton, LOW);
  digitalWrite(leftbutton, LOW);
  digitalWrite(rightbutton, LOW);
  digitalWrite(upbutton, LOW);
  digitalWrite(downbutton, LOW);
    lcd.clear();
  lcd.setCursor(0, 0);
  digitalWrite(13, HIGH);
  Serial.println("DONE");
  delay(9999999999999999999999);

}

void changeSetPoint(long degrees) {
  Serial.println("Pushing menu");
  pushButton(menubutton, 1);
  Serial.println("Pushing right");
  pushButton(rightbutton, 3);
  
  if (degrees > 0) {
    Serial.println("Pushing up");
    pushButton(upbutton, degrees);
  }
  else {
    Serial.println("Pushing down");
    pushButton(downbutton, degrees * -1);
  }
  goHome();
}

void goHome() {
  //Serial.println("GOING HOME");
  pushButton(homebutton, 1);
}

void pushButton(int button, int times) {
  for (int i = 1; i <= times; i++) {
    long time1 = millis();
    //Serial.println("PUSH!");
    while (millis() < time1 + 200) {
      digitalWrite(button, HIGH);

    }
    while (millis() < time1 + 500) {
      digitalWrite(button, LOW);
    }
  }
}

/*long getNumber(unsigned int digits) {
  long digit[4] = {0, 0, 0, 0};

  lcd.setCursor(0,1);
  lcd.print("000");

  for (unsigned int i = digits; i >= 1; i--)
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
        switch(i) {
          case 3:
          lcd.setCursor(0, 1);
          break;
          case 2:
          lcd.setCursor(1, 1);
          break;
          case 1:
          lcd.setCursor(2, 1);
          break;
        }
        Serial.println(digit[i]);
        lcd.print(digit[i]);
        delay(250);
      }
      /*else if (digitalRead(buttondown) == HIGH) {
        digit[i]--;
        Serial.print(digit[i]);
        delay(150);
      }
    }
    delay(250);
  }
  /*Serial.println(digit[1]);
  Serial.println(digit[2]);
  Serial.println(digit[3]);
  
  Serial.print("3: ");
  Serial.println(digit[3]);
  Serial.print("2: ");
  Serial.println(digit[2]);
  Serial.print("1: ");
  Serial.println(digit[1]);
  long returnval = (digit[3] * 100) + (digit[2] * 10) + digit[1];
  //Serial.print("RETURNIN!!! ");
  Serial.println(returnval);
  return returnval;
}*/

unsigned long getNumber(int numberofdigits) {
//Serial.println(numberofdigits);
stringcomplete = 0;
char number[numberofdigits];
unsigned long returnval;
char incomingByte;
//Serial.flush();

  while (!stringcomplete) {

while (Serial.available() > 0) {
  
  returnval = 0;
  while(1) {
    incomingByte = Serial.read();
    if (incomingByte == 10) break;
    if (incomingByte == -1) continue;
    returnval *= 10;
    returnval = ((incomingByte -48)+returnval);
      }
      stringcomplete = 1;
      Serial.println(returnval);
      return returnval;
      
}
  }
returnval = atol(number);
Serial.println(returnval);
stringcomplete = 1;
return returnval;


}
