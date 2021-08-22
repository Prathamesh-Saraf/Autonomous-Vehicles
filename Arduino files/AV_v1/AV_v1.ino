#include <Servo.h>          
#include <NewPing.h>      
#include <Stepper.h>

#define trig_pin 3 
#define echo_pin 2 

#define maximum_distance 200
boolean goesForward = false;
int distanceR;
int distanceL;
int num;
int lastCall;
int distance = 100;
int stepsInRev = 200;
int num_of_steps = 1;
String inString = "";

NewPing sonar(trig_pin, echo_pin, maximum_distance); 
Servo servo_motor; 
Stepper myStepperR(stepsInRev, 7, 6, 5, 4);
Stepper myStepperL(stepsInRev, 8, 9, 10, 11);


void setup(){
  Serial.begin(9600);
  while (!Serial) {
      ;
  }
  Serial.println("\n\nString toFloat():");
  Serial.println();
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  servo_motor.attach(12); 

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){
  int distance= sonar.ping_cm();
  int duration= sonar.ping();
  int speed1= (distance*10000)/(duration);
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){
    slowDown(num_of_steps);
    delay(1000);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if ((speed1<=1)&&(distanceR >= distanceLeft)){
      turnRight(num_of_steps);
      moveForward(num_of_steps);
      delay(1000);
      turnLeft(num_of_steps);
      moveForward(num_of_steps);
      distanceLeft= lookLeft();
      if(distanceL>=10){
        turnLeft(num_of_steps);
        moveForward(num_of_steps);
        delay(1000);
        turnRight(num_of_steps);
        moveForward(num_of_steps);
      }
      else{
          moveForward(num_of_steps);
        }    
    }
    else if((speed1<=1)&&(distanceL > distanceRight)){
      turnLeft(num_of_steps);
      moveForward(num_of_steps);
      delay(1000);
      turnRight(num_of_steps);
      moveForward(num_of_steps);
      distanceRight= lookRight();
      if(distanceR>=10){
        turnRight(num_of_steps);
        moveForward(num_of_steps);
        delay(1000);
        turnLeft(num_of_steps);
        moveForward(num_of_steps);
      }
      else{
          moveForward(num_of_steps);
        }    
    }
    else if((speed1<=1)&&(distanceR<=10)&&(distanceL<=10)){
      allStop();
    }
    else if(speed1==1){
      reduceSpeed(num_of_steps);
    }
    
  }
  else{
    moveForward(num_of_steps); 
  }
    distance = readPing();
    
 if (Serial.available() > 0) {
    int num;
    int inChar = Serial.read();
    if (isDigit(inChar)) {
     
      inString += (char)inChar;
     
    }
    
     if (inString=="0"){
       for(int l=0;;l++){
       moveForward(num_of_steps);
    }
     }
    if (inString>"0"){
      for(int j=0;;j++){
      turnRight(num_of_steps);
      //}
    }
     if (inString<"0"){
      for(int i=0;;i++){
      turnLeft(num_of_steps);
    }
     }
     if (inString==" "){
      for(int k=0;;k++){
      allStop();
    }
     }
    if (inChar == '\n') {
      int num = inString.toInt();
        
    }
int lastCall = num;
}
 }
else{
    num = lastCall;
    int inChar = Serial.read();
    if (isDigit(inChar)) {
     
      inString += (char)inChar;
     
    }
    
     if (inString=="0"){
       for(int l=0;;l++){
       moveForward(num_of_steps);
    }
     }
    if (inString>"0"){
      for(int j=0;;j++){
      turnRight(num_of_steps);
      }
    }
     if (inString<"0"){
      for(int i=0;;i++){
      turnLeft(num_of_steps);
    }
     }
     if (inString==" "){
      for(int k=0;;k++){
      allStop();
    }
     }
    if (inChar == '\n') {
      int num = inString.toInt();
        
    }
int lastCall = num;
inString = "";
}
}
int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distanceR = readPing();
   Serial.println(distanceR);
  delay(100);
  servo_motor.write(115);
  return distanceR;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distanceL = readPing();
  delay(100);
  servo_motor.write(115);
  Serial.println(distanceL);
  return distanceL;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}
void moveForward(int steps){
  
   if(!goesForward){

    goesForward=true;

  Serial.println("forward");
  myStepperR.setSpeed(60);
  myStepperL.setSpeed(60);
  myStepperR.step(1);
  myStepperL.step(1);
  delay(10);
  }
}

void moveBackward(int steps){

    goesForward=false;

  Serial.println("backward");
  myStepperR.setSpeed(40);
  myStepperL.setSpeed(40);
  myStepperR.step(-1);
  myStepperL.step(-1);
  delay(10);
  
}

void reduceSpeed(int steps){

  Serial.println("reduced speed");
  myStepperR.setSpeed(40);
  myStepperL.setSpeed(40);
  myStepperR.step(1);
  myStepperL.step(1);
  delay(10);
  
}

void turnRight(int steps){

  Serial.println("right");
  myStepperR.setSpeed(30);
  myStepperL.setSpeed(30);
  myStepperR.step(-1);
  myStepperL.step(1);
  delay(10); 
}

void turnLeft(int steps){

  Serial.println("left");
  myStepperR.setSpeed(30);
  myStepperL.setSpeed(30);
  myStepperR.step(1);
  myStepperL.step(-1);
  delay(10);
}
//void speed1(){
  //int distance= sonar.ping_cm();
  //int duration= sonar.ping();
  //int speed1= (distance*10000)/(duration);
  //delay(1000);
  
//}
void slowDown(int steps){
  Serial.println("slowed down");
  myStepperR.setSpeed(30);
  myStepperL.setSpeed(30);
  myStepperR.step(1);
  myStepperL.step(1);
  delay(10);  
}

void allStop(){
  Serial.println("stop");
  PORTD = B00000000; 
  PORTB = B00000000;
}
