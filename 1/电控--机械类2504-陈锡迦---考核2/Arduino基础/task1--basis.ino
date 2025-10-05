#include <Servo.h>
Servo base , fArm , rArm , claw;

int basepos=90;
int rArmpos=90;
int fArmpos=90;
int clawpos=90;
const int basemin=0;
const int basemax=180;
const int rArmmin=55;
const int rArmmax=135;
const int fArmmin=80;
const int fArmmax=150;
const int clawmin=25;
const int clawmax=150;

int Delay=50;

void setup() {
  base.attach(11);
  delay(200);
  rArm.attach(10);
  delay(200);
  fArm.attach(9);
  delay(200);
  claw.attach(6);
  delay(200);
  Serial.begin(9600);
  Serial.println("welcome");
  }

void loop() {
  if (Serial.available()>0){
    char serialCmd = Serial.read();
    armDataCmd(serialCmd);}}


void arm1(char servoCmd, int topos ,int  Delay){
  Servo servogo2;
  int frompos;
  switch(servoCmd){
    case'b':
    if (topos>=basemin && topos<=basemax){
      servogo2=base;
      frompos=base.read();
      break;
    }
    else{
     Serial.println("out of limit");
      return;
    }
    
    case'c':
    if (topos>=clawmin && topos<=clawmax){
      servogo2=claw;
      frompos=claw.read();
      break;
    }
    else{
    Serial.println("out of limit");
      return;
    }

    
    case'f':
    if (topos>=fArmmin && topos<=fArmmax){
      servogo2=fArm;
      frompos=fArm.read();
      break;
    }
    else{
     Serial.println("out of limit");
      return;
    }

    
    case'r':
    if (topos>=rArmmin && topos<=rArmmax){
      servogo2=rArm;
      frompos=rArm.read();
      break;
    }
    else{
     Serial.println("out of limit");
     return;
    }
  }
  
if(frompos<=topos){
      for(int i=frompos;i<=topos;i++){
        servogo2.write(i);
        delay(Delay);}
      }
      else{
        for(int i=frompos;i>=topos;i--){
        servogo2.write(i);
        delay(Delay);}
     }

 }
void arm2(){
int action[11][3]{
  {'b',120,50},
   {'c',120,50},
    {'f',80,50},
     {'r',135,50},
      {'c',80,50},
       {'b',70,50},
        {'c',110,50},
         {'r',90,50},
         {'c',90,50},
         {'f',90,50},
         {'b',90,50},

};
for (int i=0; i<11;i++){
  arm1(action[i][0],action[i][1],action[i][2]);
}
}  
void reportStatus(){
  Serial.println("");
  Serial.println("");
  Serial.println("Report");
  
}


void armDataCmd(char servoCmd){
  Serial.print("servoCmd=");
  Serial.print(servoCmd);

  int frompos;
  int topos;
if ( servoCmd=='c' ||  servoCmd=='b' ||servoCmd=='f' ||servoCmd=='r' ){
  int servoData = Serial.parseInt();
  Serial.println(servoData);
  arm1(servoCmd,servoData,Delay);
}
else{
  switch(servoCmd){
    case 'o':
    reportStatus();
    break;

    case 'p':
    arm2();

    default:
    Serial.println("Unknown");}}
}
