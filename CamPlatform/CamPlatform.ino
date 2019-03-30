// Design for the Robotic platform
// ref: https://playground.arduino.cc/ComponentLib/Servo/
// ref: servo and data type control from serial monitor: https://jingyan.baidu.com/article/6181c3e0a6e75b152ef15399.html
#include <Servo.h>
#include <string.h>
#include <stdio.h>
#define SOFT_START_CONTROL_PIN 12
#define SERVO_PIN_1 11
#define SERVO_PIN_2 6

Servo sev_1; 
Servo sev_2;

void setup() {

  Serial.begin(9600);    

  bool doSoftStart = 1;

  if (doSoftStart)
  {
    pinMode(SOFT_START_CONTROL_PIN, OUTPUT);
    digitalWrite(SOFT_START_CONTROL_PIN, HIGH);
  }

  sev_1.attach(SERVO_PIN_1);
  delay(15);
  sev_2.attach(SERVO_PIN_2);
  delay(15);
  //sev_2.write(20); 
  //delay(1000);

  digitalWrite(SOFT_START_CONTROL_PIN, LOW);
 
}

void loop() {

  int servo_array[3]; 
  int flag_stop = 0; 

  if(Serial.available()){

    String message= Serial.readString();

    // Stop the program
    if (message.toInt() == 0){
      Serial.print("Stop the program");
      digitalWrite(SOFT_START_CONTROL_PIN, LOW);
      flag_stop = 1; 
    }

    // Servo Control
    if (flag_stop == 0){
      int commaPosition;
      Serial.println(message);
      int idx = 0; 
      do{
        commaPosition = message.indexOf(',');
        if(commaPosition != -1){
          //Serial.println(message.substring(0,commaPosition));
          servo_array[idx] = message.substring(0,commaPosition).toInt();
          message = message.substring(commaPosition+1, message.length());
        }
        else{
          if(message.length() > 0){
            //Serial.println(message);  
            servo_array[idx] = message.substring(0,commaPosition).toInt();
          }
        }
        idx = idx + 1;
      }
      while(commaPosition >=0);
      int servo_number = servo_array[0];
      int servo_angle_1 = servo_array[1];
      int servo_angle_2 = servo_array[2]; 
      Serial.println(servo_array[0]);
      Serial.println(servo_array[1]);
      Serial.println(servo_array[2]); 
  
      sev_1.write(servo_angle_1);
      sev_2.write(servo_angle_2);
  
      int sev_currentangle_1 = sev_1.read();
      Serial.print("The current angle is ");
      Serial.println(sev_currentangle_1);
      delay(1000);
      int sev_currentangle_2 = sev_2.read();
      Serial.print("The current angle is ");
      Serial.println(sev_currentangle_2);
      
      delay(5000);  
    } 
  }
}

//  int sev_read_1 = analogRead(SERVO_PIN_1); 
//  int sev_read_2 = analogRead(SERVO_PIN_2); 
//  sev_read_1 = map(sev_read_1, 0, 1023, 0, 180); 
//  sev_read_2 = map(sev_read_2, 0, 1023, 0, 180); 
