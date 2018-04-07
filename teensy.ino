#include <Servo.h>
#include <Wire.h>
#define PHOTO_THRESHOLD 200
Servo servo;
Servo esc;
const int photo = A0;
byte bot_speed = 90, dir = 90;

void setup() {
  // put your setup code here, to run once:
  servo.attach(6); // steering
  esc.attach(5); // speed
  pinMode(13, OUTPUT);
  pinMode(23, INPUT_PULLUP);
  pinMode(photo, INPUT_PULLUP);
  arm();
  Wire.begin(19);
  Wire.onReceive(controlEvent);
}

void arm() {
  esc.write(90);
  digitalWrite(13, HIGH);
  while(digitalRead(23)){
    delay(1);  
  }
  digitalWrite(13, LOW);
}

void controlEvent(int n) {
  while (Wire.available() < 2);
  bot_speed = Wire.read();
  dir = Wire.read();
}

void loop() {
  // put your main code here, to run repeatedly:
   servo.write(dir);
   esc.write(bot_speed);
  
//  servo.write(110);
////  esc.write(100);
  delay(10);
//  Serial.println(analogRead(photo));
}

//This code can be used for any purpose.

//  Servo ESC1;
//  
//  int pos = 0; //Sets position variable
//  void arm(){
//    setSpeed(0); //Sets speed variable delay(1000);
//  }
//  
//  void setSpeed(int speed){
//    int angle = map(speed, 0, 100, 0, 180); //Sets servo positions to different speeds 
//    ESC1.write(angle);
//  }
//  
//  void setup() {
//    ESC1.attach(3); //Adds ESC to certain pin. arm();
//  }
//  
//  void loop() {
//   int speed; //Implements speed variable
//    for(speed = 0; speed <= 70; speed += 5) { //Cycles speed up to 70% power for 1 second
//      setSpeed(speed); //Creates variable for speed to be used in in for loop
//      delay(1000);
//    }
//    delay(4000); //Stays on for 4 seconds
//    for(speed = 70; speed > 0; speed -= 5) { // Cycles speed down to 0% power for 1 second
//      setSpeed(speed); delay(1000);
//    }
//    setSpeed(0); //Sets speed variable to zero no matter what
//    delay(1000); //Turns off for 1 second
//  }

