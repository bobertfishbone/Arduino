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




// PROBABLY DON'T CHANGE ANYTHING BELOW THIS!

long numSteps = 0;
long initialtemp;
unsigned int hours = 0;
unsigned int minutes = 0;
bool stringcomplete = 0;
long myTemp[10];
long stageDuration[10];

long startTime;
long stageStart;

int acceleration = 1000; // Steps per second per second, up to max speed
long millistart; // Grabs milliseconds since power on once motor has initially stepped.
bool run = false; // Has the cycle ended?
long oldPosition = 0; // Encoder reference point
// Create motor, encoder objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Encoder enc(2, 5);
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 1);
AccelStepper stepper(forwardStep, backwardStep);
void forwardStep()
{
  myMotor->onestep(FORWARD, MICROSTEP);
}

void backwardStep()
{
  myMotor->onestep(BACKWARD, MICROSTEP);
}






void setup() {

  
  // put your setup code here, to run once:
  AFMS.begin();

  stepper.setMaxSpeed(maxspeed);
  stepper.setAcceleration(acceleration);
  //stepper.setCurrentPosition(0);
  stepper.runToNewPosition(numberofSteps);
  
  millistart = millis();
}

void loop() {
 if (run == false){
  // put your main code here, to run repeatedly:
  stepper.setMaxSpeed(maxspeed);
  stepper.setAcceleration(acceleration);
  long newPosition = enc.read();



  if (newPosition != oldPosition)
  {
    if (newPosition > oldPosition)
    {
      stepper.moveTo(stepper.currentPosition() + encoderSteps*(newPosition - oldPosition));
      
    }
    else
    {
      stepper.moveTo(stepper.currentPosition() - encoderSteps*(oldPosition - newPosition));
    }
  }


  oldPosition = newPosition;
  stepper.run();
  
  if (millis() > millistart + duration)
  {
    if (run == false)
    {

      stepper.setMaxSpeed(maxspeed);
      stepper.setAcceleration(acceleration);
stepper.runToNewPosition(0);
      run = true;
      myMotor->release();
    }

  }
 }

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
