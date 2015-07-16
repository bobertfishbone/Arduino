#define homebutton 0
#define menubutton 1
#define leftbutton 2
#define rightbutton 3
#define upbutton 4
#define downbutton 5

#define buttonup 6
#define buttondown 7
#define buttonselect 8

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
    while (digitalRead(buttonselect) == HIGH) {
      if (digitalRead(buttonup) == LOW) {
        digit[i]++;
        Serial.print(digit[i]);
        delay(150);
      }
      else if (digitalRead(buttondown) == HIGH) {
        digit[i]--;
        Serial.print(digit[i]);
        delay(150);
      }
    }
    delay(150);
  }
  int returnval = (digit[1]*100) + (digit[2] * 10) + digit[3];
  return returnval;
}

