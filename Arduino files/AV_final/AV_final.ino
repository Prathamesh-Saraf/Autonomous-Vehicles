#include <Servo.h>          
#include <NewPing.h>      
#include <Stepper.h>

#define trig_pin 3 
#define echo_pin 2 

#define maximum_distance 200
boolean goesForward = false;
int distanceR;
int distanceL;
int n;
int lastCall;
int distance = 100;
int stepsInRev = 200;
int num_of_steps = 1;
int distanceright;
int distanceleft;
String readString;

NewPing sonar(trig_pin, echo_pin, maximum_distance); 
Servo servo_motor;
Servo servo_motorR;
Servo servo_motorL;
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
  servo_motorR.attach(22); 
  servo_motorL.attach(23); 

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
  //delay(50);
   while (Serial.available()) {
    char c = Serial.read(); 
    readString += c; 
    delay(2);  
  }
  if (readString.length() >0) {
    Serial.println(readString);       
    n = readString.toInt();
    int num=90+n;    
    servo_motorR.write(num);
    servo_motorL.write(num);
     
bailout: 
    readString=""; 
  }
 
  
 while(distance>=20 || distance==0){
 moveStraight(num_of_steps);
 distance = readPing();
 
  
  
 }
 

  if (distance < 20){
    Serial.println(distance);
  
    delay(1000);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if ((distanceRight >= distanceLeft)&&(distanceRight>=10))
    {  slowDown(num_of_steps);
      servo_motorR.write(45);
      servo_motorL.write(45);
      servo_motor.write(-50);
      Serial.println("working");
      int n=0;
       distance=readPing();
      
     
      while(0< distance<10)
      {
        n=n+1;
        moveStraight(num_of_steps);
        Serial.println("loop1");
      distance=readPing();
      Serial.println(distance);
      delay(10);
        
      }
      
      servo_motorR.write(0);
      servo_motorL.write(0);
      while (distanceLeft>50)
      {
        Serial.println("moving wforward from side");
      moveStraight(num_of_steps);
      distanceleft=readPing();
     
      }
     while(distanceleft<50);
     {
        Serial.println("moving forward parallel to next car");
     moveStraight(num_of_steps);
     distanceleft=readPing();
     }
     servo_motorR.write(-45);
      servo_motorL.write(-45);
      for(int i=0;i<=n;i++)
        Serial.println("coming in back on track");
       moveStraight(num_of_steps);
       servo_motorR.write(0);
      servo_motorL.write(0);
      moveStraight(num_of_steps);
       
      
     
     
     /* if(distanceL>=10)
      {
        turn(num_of_steps);
         //Serial.println("2");
        moveStraight(num_of_steps);
        delay(1000);
        turn(num_of_steps);
        moveStraight(num_of_steps);
      }*/
    }
      else{
          moveForward(num_of_steps);
        }    
    }
    else if((distanceLeft > distanceRight)&&(distanceLeft>=10))
    {  slowDown(num_of_steps);
    Serial.print("left");
      servo_motorR.write(-45);
      servo_motorL.write(-45);
      turn(num_of_steps);
      delay(2000);
      //Serial.println("3");
      servo_motorR.write(0);
      servo_motorL.write(0);
      moveStraight(num_of_steps);
      delay(4000);
      servo_motorR.write(45);
      servo_motorL.write(45);
      turn(num_of_steps);
      delay(2000);
      servo_motorR.write(0);
      servo_motorL.write(0);
      moveStraight(num_of_steps);
      distanceR= checkRight();
      if(distanceR>=10){
        turn(num_of_steps);
        moveStraight(num_of_steps);
        delay(1000);
        turn(num_of_steps);
        // Serial.println("4");
        moveStraight(num_of_steps);
      }
      else{
          moveForward(num_of_steps);
        }    
    }
     else if((distanceRight<=10)&&(distanceLeft<=10)){
      allStop();
      
      }
   
    else if(speed1==1){
      reduceSpeed(num_of_steps);
      
    }
   
      
     
     
    
    
  
  else{
    
    moveForward(num_of_steps);
    
  }
  
   distance = readPing();
   
}
 


int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distanceR = readPing();
  Serial.print("right:");
   Serial.println(distanceR);
  delay(100);
  servo_motor.write(115);
  return distanceR;
}
int checkRight(){  
  servo_motor.write(70);
  delay(500);
  int distanceRig = readPing();
  Serial.print("right:");
   Serial.println(distanceRig);
  delay(100);
  servo_motor.write(115);
  return distanceRig;
}
int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distanceL = readPing();
  delay(100);
  servo_motor.write(115);
  Serial.print("left:");
  Serial.println(distanceL);
  return distanceL;
  delay(100);
}
int checkLeft(){
  servo_motor.write(170);
  delay(500);
  int distanceLef = readPing();
  delay(100);
  servo_motor.write(115);
  Serial.print("left:");
  Serial.println(distanceLef);
  return distanceLef;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  
  return cm;
}
void moveForward(int steps){
  
   if(!goesForward){

    goesForward=true;

  Serial.println("forward");
  myStepperR.setSpeed(80);
  myStepperL.setSpeed(80);
  myStepperR.step(1);
  myStepperL.step(1);
  delay(10);
  }
}
void moveStraight(int steps){
 
   
  Serial.println("forward");
  myStepperR.setSpeed(60);
  myStepperL.setSpeed(60);
  myStepperR.step(1);
  myStepperL.step(1);
  delay(10);
  
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
void turn(int steps){

  Serial.println("turning");
  myStepperR.setSpeed(50);
  myStepperL.setSpeed(50);
  myStepperR.step(1);
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
  myStepperR.setSpeed(0);
  myStepperL.setSpeed(0);
  delay(10); 
  distance = readPing();
}
/*int readPing1(){
  delay(70);
  int cm = sonar.ping_cm();
  
  return cm;
}
int readPing2(){
  delay(70);
  int cm = sonar.ping_cm();
  
  return cm;
}*/

