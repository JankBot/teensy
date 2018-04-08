#include <Servo.h>
#include <Wire.h>

#define PHOTO_THRESHOLD 200
#define WATCHDOG_TIMEOUT 20

const int photo = A0;
const int start_btn = 23;
const int status_led = 13;

Servo servo;
Servo esc;

byte bot_speed = 90, dir = 90;
byte watchdog_count = 0;

void setup() {
  // set pin modes
  pinMode(status_led, OUTPUT);
  pinMode(start_btn, INPUT_PULLUP);
  pinMode(photo, INPUT_PULLUP);

  // setup servo channels
  servo.attach(6); // steering
  esc.attach(5); // speed

  // start inbound I2C
  Wire.begin(19);
  Wire.onReceive(controlEvent);

  // Wait for esc to arm
  arm();
}

void arm() {
  esc.write(90);

  // wait for manual signal to proceeed
  digitalWrite(status_led, HIGH);
  while(digitalRead(start_btn)){
    delay(1);  
  }
  digitalWrite(status_led, LOW);
}

void controlEvent(int n) {
  if (n < 2) return;

  bot_speed = Wire.read();
  dir = Wire.read();
  watchdog_count = 0;
}

void loop() {
  if (watchdog_count > WATCHDOG_TIMEOUT) {
    dir = 0;
    bot_speed = 0;
  }

  servo.write(dir);
  esc.write(bot_speed);
  watchdog_count++;

  delay(10);
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

