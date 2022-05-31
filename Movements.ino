#include <Servo.h> 

int neckSidePin = 4, neckUpPin = 5, armPin = 6;
Servo joints[3];
const int  neckSide = 2, neckUp = 1, arm = 0;

int armZero = 90;
int helloMax = 180;
int helloMin = 140;
int hello[3][3][6] = {{{armZero, helloMax, helloMin, helloMax, helloMin, armZero},{0, 500, 1000, 1500, 2000, 2500},{0, 10, -10, 10, -10, -10}},{},{}};

int nodZero = 90;
int yesZero = 90;
int nodUp = 120;
int yesLeft = 120;
int yesRight = 60;
int lookAround[3][3][6] = {{},{{yesZero,yesRight,yesRight,yesLeft,yesLeft,yesZero},{500,1000,1500,2000,2500,3000},{10,0, -10, 0, 10, 0}},{{nodZero, nodUp, nodUp, nodUp, nodUp, nodZero},{500,1000,1500,2000,2500,3000},{0, 10, 0, 0, 0, -10}}};

int reachedPosition[3] = {0,0,0};

unsigned long movementStartTime = 0;
unsigned long prevMovementTime = 0;

int movements[2][3][3][6];

bool prevMOVE = false;

void movementsSetup(){
  Serial.begin(9600);
  for(int j=0; j<3; j++){
    for(int k=0; k<3; k++){
      for(int m=0; m<6; m++){
        movements[0][j][k][m] = hello[j][k][m];
        movements[1][j][k][m] = lookAround[j][k][m];
      }
    }
  }
  
  joints[neckSide].attach(neckSidePin); 
  joints[neckUp].attach(neckUpPin);
  joints[arm].attach(armPin); 
  
  joints[arm].write(90); 
  joints[neckUp].write(90); 
  joints[neckSide].write(90); 
  MOVE = 1;
  Serial.println("begin");
}

int angles[3] = {90,90,90};
float floatAngles[3] = {0,0,0};

void movementsLoop(){
  if(Serial.available()){
    MOVE = Serial.parseInt();
    Serial.read();
    Serial.print(MOVE);
    Serial.print(reachedPosition[i]);
  }
  //TODO movements associated to a joke
  //TODO random movements
  if(MOVE && !prevMOVE){
    movementStartTime = millis();
    Serial.print("start move, ");
    Serial.println(movementStartTime);
    reachedPosition[0] = 0;
    reachedPosition[1] = 0;
    reachedPosition[2] = 0;
  }
  if(MOVE){
    unsigned long currTime = millis();
    if(MOVE == 1){
    for(int i = 0; i < 1; i++){
      if(reachedPosition[i] <= 5){
        if(int(currTime - movementStartTime) < movements[MOVE-1][i][1][reachedPosition[i]]){
          if(int(currTime-prevMovementTime) > 50){
            if (angles[i] != movements[MOVE-1][i][0][reachedPosition[i]]){
                angles[i]+= movements[MOVE-1][i][2][reachedPosition[i]];
                joints[i].write(angles[i]);
            }
              //float(currTime-prevMovementTime) * (float(movements[MOVE-1][i][0][reachedPosition[i]])-float(movements[MOVE-1][i][0][reachedPosition[i]-1]))/(float(movements[MOVE-1][i][1][reachedPosition[i]]) - float(movements[MOVE-1][i][1][reachedPosition[i]-1]));
            //Serial.println(reachedPosition[i]);
            prevMovementTime = currTime;
          }
        }
        else{
          angles[i] = movements[MOVE-1][i][0][reachedPosition[i]];
          joints[i].write(angles[i]);
          floatAngles[i] = angles[i];
          reachedPosition[i]++;
            if(i == arm){
              Serial.print(movements[MOVE-1][i][0][reachedPosition[i]]);//float(currTime - movementStartTime));
              Serial.print(",");
              Serial.print(angles[i]);
              Serial.println(reachedPosition[i]);//(float(currTime - prevMovementTime)*(float(movements[MOVE-1][i][0][reachedPosition[i]])-float(movements[MOVE-1][i][0][reachedPosition[i]-1]))/(float(movements[MOVE-1][i][1][reachedPosition[i]]) - float(movements[MOVE-1][i][1][reachedPosition[i]-1]))));
            }
        }
      }
    }
    }
    if(MOVE == 2){
    for(int i = 1; i < 3; i++){
      if(reachedPosition[i] <= 5){
        if(int(currTime - movementStartTime) < movements[MOVE-1][i][1][reachedPosition[i]]){
          if(int(currTime-prevMovementTime) > 50){
            if (angles[i] != movements[MOVE-1][i][0][reachedPosition[i]]){
                angles[i]+= movements[MOVE-1][i][2][reachedPosition[i]];
                joints[i].write(angles[i]);
            }
              //float(currTime-prevMovementTime) * (float(movements[MOVE-1][i][0][reachedPosition[i]])-float(movements[MOVE-1][i][0][reachedPosition[i]-1]))/(float(movements[MOVE-1][i][1][reachedPosition[i]]) - float(movements[MOVE-1][i][1][reachedPosition[i]-1]));
            //Serial.println(reachedPosition[i]);
            prevMovementTime = currTime;
          }
        }
        else{
          angles[i] = movements[MOVE-1][i][0][reachedPosition[i]];
          joints[i].write(angles[i]);
          floatAngles[i] = angles[i];
          reachedPosition[i]++;
        }
      }
    }
    }
    //Serial.println(reachedPosition[0]);
    if(reachedPosition[0] > 5 && reachedPosition[1] > 5 && reachedPosition[2] > 5 ){
      MOVE = 0;
      for(int i = 0; i < 3; i++){
          angles[i] = movements[MOVE-1][i][0][5];
          Serial.println( angles[i]); 
          joints[i].write(90);
        }
    }
  }
  if(!MOVE && prevMOVE){ //reset reached position
    reachedPosition[0] = 0;
    reachedPosition[1] = 0;
    reachedPosition[2] = 0;
  }
  prevMOVE = MOVE;
}

// this for loop works correctly with an array of any type or size
/*for (byte i = 0; i < (sizeof(myValues) / sizeof(myValues[0])); i++) {
  // do something with myValues[i]
}*/
