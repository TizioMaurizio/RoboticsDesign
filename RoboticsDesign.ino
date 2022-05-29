#include "DFRobotDFPlayerMini.h"

volatile int volume = 12;
char* joke;
bool speak = false;
DFRobotDFPlayerMini player; //pin to 5v

void setup() {
    // Init USB serial port for debugging
    Serial.begin(9600);
    mouthSetup();
    //microphoneSetup();
    //jokesSetup();
    //movementsSetup();
    volumeButtonsSetup();
}

void loop() {
    mouthLoop();
    //microphoneLoop();
    //jokesLoop();
    //movementsLoop();
    volumeButtonsLoop();
    //delay(1);
  }
