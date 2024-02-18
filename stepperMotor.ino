#include <Servo.h>

#define sp1 9
#define sp2 10
#define sp3 11
#define sp4 12
#include "SharpIR.h"
#define IRPin A0
#define model 100500

int distance_cm;
int stepNumber = 0;
bool running = true;
//instance create
SharpIR mySensor = SharpIR(IRPin, model);
Servo myServo;


void setup() {

  pinMode(sp1, OUTPUT);
  pinMode(sp2, OUTPUT);
  pinMode(sp3, OUTPUT);
  pinMode(sp4, OUTPUT);
  myServo.attach(6);
  Serial.begin(9600);
}

void loop() {
  //myServo.write(-90);
  while (running){
    //clockwise
    myServo.write(-90);
    for(int i = 0; i < 4; i++){
      for(int i = 0; i <= 500; i+=2){
        MotorClockwise();
        delay(2);
      }
      distance_cm = mySensor.distance();
      // Print the measured distance to serial output
      Serial.print("Mean distance: ");
      Serial.print(distance_cm);
      Serial.println(" cm");
      if ((distance_cm > 0) && (distance_cm < 71)){
        running = false;
        break;
      }
    }
    delay(1000);
    //counterclockwise
    for(int i = 0; i <= 1000; i+=2){
      MotorCounterClockwise();
      delay(2);
    }
    distance_cm = mySensor.distance();
    //Print the measured distance to serial output
    Serial.print("Mean distance: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
    if ((distance_cm > 0) && (distance_cm < 100)){
      running = false;
      break;
    }
    delay(10);
    for(int i = 0; i <= 1000; i+=2){
      MotorCounterClockwise();
      delay(2);
    }
    distance_cm = mySensor.distance();
    //Print the measured distance to serial output
    Serial.print("Mean distance: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
    if ((distance_cm > 0) && (distance_cm < 100)){
      running = false;
      break;
    }
    delay(1000);
  }
  if(!running){
    myServo.write(180);
  }

  

}


void MotorClockwise(){
  switch(stepNumber){
    case 0:
      digitalWrite(sp1, HIGH);
      digitalWrite(sp2, LOW);
      digitalWrite(sp3, LOW);
      digitalWrite(sp4, LOW);
      break;
    case 1:
      digitalWrite(sp1, LOW);
      digitalWrite(sp2, HIGH);
      digitalWrite(sp3, LOW);
      digitalWrite(sp4, LOW);
      break;
    case 2:
      digitalWrite(sp1, LOW);
      digitalWrite(sp2, LOW);
      digitalWrite(sp3, HIGH);
      digitalWrite(sp4, LOW);
      break;
    case 3:
      digitalWrite(sp1, LOW);
      digitalWrite(sp2, LOW);
      digitalWrite(sp3, LOW);
      digitalWrite(sp4, HIGH);
      break;
  }
  stepNumber++;
  if (stepNumber > 3){
    stepNumber = 0;
  }
}

void MotorCounterClockwise(){
  switch(stepNumber){
    case 0:
      digitalWrite(sp1, LOW);
      digitalWrite(sp2, LOW);
      digitalWrite(sp3, LOW);
      digitalWrite(sp4, HIGH);
      break;
    case 1:
      digitalWrite(sp1, LOW);
      digitalWrite(sp2, LOW);
      digitalWrite(sp3, HIGH);
      digitalWrite(sp4, LOW);
      break;
    case 2:
      digitalWrite(sp1, LOW);
      digitalWrite(sp2, HIGH);
      digitalWrite(sp3, LOW);
      digitalWrite(sp4, LOW);
      break;
    case 3:
      digitalWrite(sp1, HIGH);
      digitalWrite(sp2, LOW);
      digitalWrite(sp3, LOW);
      digitalWrite(sp4, LOW);
      break;
  }
  stepNumber++;
  if (stepNumber > 3){
    stepNumber = 0;
  }
}
