#include "DFRobotDFPlayerMini.h"

static const long RST=172800000; //2 gg
//volatile int volume = 12;
int volume =12;
char* joke;
bool speak = false;
int MOVE = 0;
int MOUTH_MODE = 0;
DFRobotDFPlayerMini player; //pin to 5v
long t =0;

void setup() {
    // Init USB serial port for debugging
    Serial.begin(9600);
    microphoneSetup();
    //mouthSetup();
    jokesSetup();
    movementsSetup();
    volumeButtonsSetup();
}

void loop() {
   //reset after RST time
  if(millis()>= RST){
    rst();
  }
  
    //mouthLoop();
    //microphoneLoop();
    //jokesLoop();
    movementsLoop();
    //volumeButtonsLoop();
    //delay(1);
  }

void rst(){
  asm volatile (" jmp 0");
}
