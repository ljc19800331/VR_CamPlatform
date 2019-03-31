// Design for the Robotic platform
// ref: https://playground.arduino.cc/ComponentLib/Servo/
// ref: servo and data type control from serial monitor: https://jingyan.baidu.com/article/6181c3e0a6e75b152ef15399.html
#include <Servo.h>
#include <string.h>
#include <stdio.h>
// #define SOFT_START_CONTROL_PIN 12
#define SERVO_PIN_1 11
#define SERVO_PIN_2 12

Servo sev_1; 
Servo sev_2;

void setup() {

  Serial.begin(9600);    
  sev_1.attach(SERVO_PIN_1);
  delay(15);
  sev_2.attach(SERVO_PIN_2);
  delay(15);
 
}

void loop() {

  int servo_array[3]; 
  int flag_stop = 0; 
  int myTimeout = 5;
  Serial.setTimeout(myTimeout);

  if(Serial.available()){

    String message= Serial.readString();
    
    if (flag_stop == 0){
      
      int commaPosition;
      int idx = 0; 
      int str_fg;
      String char_fg;
      char fg;
      do{
        commaPosition = message.indexOf(',');
        if(commaPosition != -1){
          if (idx == 0){
            fg = message.substring(0, commaPosition).charAt(0); 
          }
          if (idx != 0)
          servo_array[idx] = message.substring(0,commaPosition).toInt();
          message = message.substring(commaPosition+1, message.length());
        }
        else{
          if(message.length() > 0){
            servo_array[idx] = message.substring(0,commaPosition).toInt();
          }
        }
        idx = idx + 1;
      }
      while(commaPosition >=0);
      
      int servo_number = servo_array[0];
      int servo_angle_1 = servo_array[1];
      int servo_angle_2 = servo_array[2]; 
      
      if (fg == 'g'){
         Serial.print(fg);
         Serial.print(",");
         Serial.print(servo_angle_1);
         Serial.print(",");
         Serial.print(servo_angle_2);
         Serial.print("\n");
         sev_1.write(servo_angle_1);
         delay(15);
         sev_2.write(servo_angle_2); 
      }
    } 
  }
      
      int sev_currentangle_1 = sev_1.read();
      int sev_currentangle_2 = sev_2.read();
      Serial.print("f");
      Serial.print(",");
      Serial.print(sev_currentangle_1);
      Serial.print(",");
      Serial.print(sev_currentangle_2);
      Serial.print("\n");
      delay(5);
  
}
