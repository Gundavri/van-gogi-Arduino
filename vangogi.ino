#include "matrix.h"

const int pageHeight = 450;
const int pageWidth = 320;

int motorR[4] = {2,3,4,5};
int motorL[4] = {10,11,12,13};

const int height = 842/pixel+1;
const int width = 595/pixel+1;

int stepForward = pageHeight / height;

int RC[4] = {1, 1, 1, 1};
int LC[4] = {1, 1, 1, 1};

int counterR = 0;
int counterL = 0;

int counter = 1;

int x = 0, y = 0;

int direct = 1;

bool whenToTurnMore = 0;

void setup() {
  for(int i = 0; i < 4; i++){
    pinMode(motorR[i], OUTPUT);
    pinMode(motorL[i], OUTPUT);
  }
  digitalWrite(motorR[3], 0);
  digitalWrite(motorL[3], 0);
  Serial.begin(9600);
}

void loop() {
 spanThePage();
}

void spanThePage(){
  int last1 = -1;
  for(int i = 0; i < height; i++){
    if(matrix[x][i]){
      last1 = i;
    }
  }
  if(last1!=-1){
    turn();
    draw(last1);
    find1();
    direct = -direct;
    turn();
  } else {
    goForward();
    y++;
  }
}

void find1(){
  if(direct < 0) for(int i = y; i > 0; i += direct){
  
  }
  else for(int i = y; i < height; i+=direct){
  
  }
}

void draw(int last){
    y = last;
    for(int i = 0; i < last+1; i++){
      if(matrix[x][i]) moveServo();
      goForward();
    }
}

void moveServo(){
  
}

void turn(){
  for(int i = 0; i < (whenToTurnMore?790/4+1:790/4); i++){
    spinForever();
    delay(50);
  }  
  whenToTurnMore = !whenToTurnMore;
}

void goForward(){
  
}

void oneStepForward(){
  if(counterR > 3) counterR = 0;
  if(counterL > 3) counterL = 0;
  RC[counterR] = 0;
  LC[counterL] = 0;
  for(int i = 0; i < 4; i++){
    digitalWrite(motorR[i], RC[i]);
    digitalWrite(motorL[i], LC[i]);    
  }
  RC[counterR++] = 1;
  LC[counterL++] = 1;
  delay(15);
}

void spinForever(){
  if(direct == 1) {
    if(counterR > 3) counterR = 0;
    if(counterL > 3) counterL = 0;
    RC[counterR] = 0;
    LC[counterL] = 0; 
    for(int i = 0; i < 4; i++){
      digitalWrite(motorR[i], RC[i]);
      digitalWrite(motorL[3-i], LC[i]);    
    } 
    RC[counterR++] = 1;
    LC[counterL++] = 1;
    delay(15);
  }
  else {
    if(counterR > 3) counterR = 0;
    if(counterL > 3) counterL = 0;
    RC[counterR] = 0;
    LC[counterL] = 0; 
    for(int i = 0; i < 4; i++){
      digitalWrite(motorL[i], LC[i]);
      digitalWrite(motorR[3-i], RC[i]);    
    } 
    RC[counterR++] = 1;
    LC[counterL++] = 1;
    delay(15);
  } 
}
