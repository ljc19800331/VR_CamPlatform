#include <Servo.h>
#define SOFT_START_CONTROL_PIN 12
#define SOFT_START_TIME_1000

Servo base;

void setup() {
  
  Serial.begin(9600);
  int StartPosition = (90, 90, 90, 90, 90, 73);
  bool doSoftStart = 1;

  if (doSoftStart)
  {
    pinMode(SOFT_START_CONTROL_PIN, OUTPUT);
    digitalWrite(SOFT_START_CONTROL_PIN, HIGH);
  }

  base.attach(11); 
  delay(10);
  base.write(90);
  delay(1000);

  digitalWrite(SOFT_START_CONTROL_PIN, LOW);
  Serial.println("Finished");

}

void loop() 
{

}
