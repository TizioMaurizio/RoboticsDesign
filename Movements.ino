#include <Servo.h> 

int neckSidePin = 5, neckUpPin = 5, armPin = 5;
Servo neckSide, neckUp, arm;

int armZero = 90;
int helloMax = 180;
int helloMin = 140;
int hello[3][2][6] = {{{armZero, helloMax, helloMin, helloMax, helloMin, armZero},{armZero, helloMax, helloMin, helloMax, helloMin, armZero}},{},{}};



void movementsSetup(){
  neckSide.attach(neckSidePin); 
  neckUp.attach(neckUpPin);
  arm.attach(armPin); 
}

void movementsLoop(){
  //TODO movements associated to a joke
  //TODO random movements
}

// this for loop works correctly with an array of any type or size
/*for (byte i = 0; i < (sizeof(myValues) / sizeof(myValues[0])); i++) {
  // do something with myValues[i]
}*/
