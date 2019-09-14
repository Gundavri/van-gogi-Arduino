#include "matrix.h"
#include <Servo.h> 
#include <Stepper.h>

const int servoPin = A0;
Servo Servo1; 
const int drawing = 169, notDrawing = 174;

const int STEPS_PER_REVOLUTION = 2048;
int fullTurn = 5100;
const int CATCH_UP = 85;

int gapCounter = 0;

int SLP[4] = {2, 3, 4, 5}; //marcxena
int SRP[4] = {10, 11, 12, 13}; //marjvena

Stepper stepperL(STEPS_PER_REVOLUTION, SLP[0], SLP[2], SLP[1], SLP[3]); //marcxena
Stepper stepperR(STEPS_PER_REVOLUTION, SRP[0], SRP[2], SRP[1], SRP[3]); //marjvena

int counter = 0;

int stepMultiplier = 30;
bool facingNorth = 1;

int x = 0;

bool down = 0;

void setup(){
  Servo1.attach(servoPin);
  Servo1.write(drawing);
  delay(2000); 
  Servo1.write(notDrawing);
  stepperL.setSpeed(20);
  stepperR.setSpeed(20);
  delay(5000);
}

void loop(){
  if(x<151) drawColumn();
}

void drawColumn(){
  if(arr[x]==0 && arr[x+1]==0){
    goForward(1);
  }
  else {
    stepMultiplier = 30;
    if(facingNorth) fullTurn=5084;
    else fullTurn=5112;
    turn90();
    String binary = toBinary();
    draw(binary);
    gapCounter++;
    facingNorth = !facingNorth;
    if(!facingNorth) fullTurn=5088;
    else fullTurn=5104;
    turn90();
//    if(gapCounter<=3) 
//    {
//      if(facingNorth) stepMultiplier = 30;
//      else stepMultiplier = 38;
//    }
//    else {
//      if(facingNorth) stepMultiplier = 18;
//      else stepMultiplier = 26;        
//    }
    if(facingNorth) stepMultiplier = 21;
    else stepMultiplier = 25;      
    goForward(1);
  }
}

void moveServo(bool next1){
  if((down && next1) || (!down && !next1)) {
    return;
  }
  if(down && !next1) {
    Servo1.write(notDrawing);
    delay(30);
    down = 0;
    return;
  }
  if(!down && next1) {
    Servo1.write(drawing);
    delay(30);
    down=1;  
    return;
  }
}

void draw(String binary){
  if(facingNorth){
    for(int i = -1; i < 106; i++){
      moveServo(binary[i+1]-'0');
      goForward(0); 
    }
  }
  else {
    for(int i = 107; i >= 1; i--){
      moveServo(binary[i-1]-'0');
      goForward(0);
    }  
  }
  moveServo(0);
}

String toBinary(){
  String result1 = "";
  long long tmp = arr[x]; 
  while(tmp!=0){
    result1 = (tmp%2==1?"1":"0") + result1;
    tmp/=2;
  }
  for(int i = result1.length(); i < 53; i++){
    result1 = "0" + result1;
  }
  String result2 = "";
  tmp = arr[x+1];
  while(tmp!=0){
    result2 = (tmp%2==1?"1":"0") + result2;
    tmp/=2;
  }
  for(int i = result2.length(); i < 53; i++){
    result2 = "0" + result2;
  }
  return result1+result2;
}

void turn90(){
  for(int i = 0; i < (fullTurn)/4; i++){
    spinForever();
  }
}

void spinForever(){
  if(facingNorth) {
    turnLeft();
  }
  else {
    turnRight();
  } 
}

void goForward(bool x_y){
  for(int i = 0; i < stepMultiplier; i++){
    oneStepForward();
  }
  x_y ? x+=2 : 1;  
}

void oneStepForward(){
    if(counter != CATCH_UP) stepperL.step(1);
    else counter = -1;
    stepperR.step(1); 
    delay(5);
    counter++;
}

void turnRight() {
   if(counter != CATCH_UP) stepperL.step(1);
   else counter = -1;
   stepperR.step(-1);
   delay(5);
   counter++;
}

void turnLeft() {
   if(counter != CATCH_UP) stepperL.step(-1);
   else counter = -1;
   stepperR.step(1);
   delay(5);
   counter++;
}
