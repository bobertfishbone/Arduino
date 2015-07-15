bool ledAOn = false;
String inputString = "";
boolean stringComplete = false;
String ledAOnText = "";
long increment = 0;
char device = 'A';

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
inputString.reserve(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(device+String(increment));
  increment++;
if (ledAOn == true) {
  digitalWrite(13, HIGH);  
}
else digitalWrite(13, LOW);


if (stringComplete) {
  if (inputString == "toggle\n")
  {
  if (ledAOn) {
    ledAOn = false;
    ledAOnText = "false";
  }
  else {ledAOn = true;
  ledAOnText = "true";}
  Serial.println(ledAOnText);
  }
  inputString = "";
  stringComplete = false;
}
}

void serialEvent() {
while(Serial.available()){
  char inChar = (char)Serial.read();
  inputString += inChar;
  if (inChar == '\n') {
    stringComplete = true;
  }
}
  
}

