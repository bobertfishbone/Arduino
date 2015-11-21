#include <AccelStepper.h>
#include <Wire.h>
#include <Encoder.h>
#include <Adafruit_MotorShield.h>

// THINGS YOU CAN CHANGE!
// * CHANGE THIS TO SET IT TO TWO HOURS FOR PRODUCTION *
// long duration = 7200000; // 2 hours in milliseconds
long duration = 10000; // 10 seconds in milliseconds (comment this out for production)
int numberofSteps = 1800; // Number of steps initially taken (3200 steps per rotation)
int maxspeed = 40; // Number of steps per second
int encoderSteps = 8; // Raise or lower this to make each encoder step move the motor more or less (granularity setting)

long numSteps = 0;
unsigned int hours = 0;
unsigned int minutes = 0;
bool stringcomplete = 0;
long mySteps[10];
long stageDuration[10];

long startTime;
long stageStart;

int acceleration = 1000;
long oldPosition = 0;
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Encoder enc(2, 5);
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);
AccelStepper stepper(forwardStep, backwardStep);

void forwardStep()
{
  myMotor->onestep(FORWARD, MICROSTEP);
}

void backwardStep()
{
  myMotor->onestep(BACKWARD, MICROSTEP);
}

void setup()
{
  Serial.begin(9600);
  AFMS.begin();
  stepper.setMaxSpeed(maxspeed);
  stepper.setAcceleration(acceleration);


  Serial.println("How many stages?");
  numSteps = getNumber(1);

  for (int i = 1; i <= numSteps; i++) {
    Serial.print("Setpoint for stg ");
    Serial.println(i);
    mySteps[i] = getNumber(4);

    Serial.print("Duration (mins) for stg ");
    Serial.println(i);
    stageDuration[i] = getNumber(3) * 60000;
  }

  startTime = millis();
}

void loop() {

  for (int i = 1; i <= numSteps; i++) {

    stepper.runToNewPosition(mySteps[i]);
    myMotor->release();
    stageStart = millis();
    while ((millis() - stageStart) < stageDuration[i])
    {
      Serial.println((millis() - stageStart)/1000);
      
    }

  }

  stepper.runToNewPosition(0);

  myMotor->release();
  Serial.println("done");
  delay(999999999999999999);
}

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
      while (1) {
        incomingByte = Serial.read();
        if (incomingByte == 10) break;
        if (incomingByte == -1) continue;
        returnval *= 10;
        returnval = ((incomingByte - 48) + returnval);
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

