#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Servo.h> 

// MP3 and motors
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX (giallo?)
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX (verde?)
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
int mouthPin = 4;
Servo mouth;
//DFRobotDFPlayerMini player; //pin to 3.3v
int mouthTime_reset = 40; //cooldown for closing mouth
int speakerPin = A0;
int maxMouthAngle = 30;
//int volume = 15;
//String joke = "";

//Move and talk///////////////////////////
int vol=0;
int i = 0;
int k = 0;
int threshold = 17;
int printTime = 0;
int mouthTime = 0;
int maxLoudness = 0;
int servoAngle = 0;
int targetAngle = 0;

void mouthSetup(){
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);
  mouth.attach(mouthPin); 

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
   Serial.println("OK");
    // Set volume (0 to 30).
    // TODO Play "hello" MP3 file on the SD card
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void mouthLoop(){
  if(Serial.available()){
    player.next();
    Serial.read();
    Serial.println("Next sound");
  }
  int analogValue = analogRead(speakerPin);
  int loudness = (analogValue-340)*(analogValue-340);// 3.3V: -340, 5V: -512
  
  if((loudness<1000)&&(loudness>-1000)){
    maxLoudness = max(maxLoudness, loudness);
  }
  
  printTime++;
  if(printTime >= 9){ //every 9 times this is called (loop time + 1ms)
    if(maxLoudness>400){//TODO and MP3BUSY
      mouth.write(maxMouthAngle + 30);
      //TODO maybe also nod with neck for more mouth movement?
      Serial.println(maxLoudness);
      mouthTime = mouthTime_reset;
    }
    else{
      if(mouthTime >= 10){
        mouthTime -= 10;
        Serial.println(maxLoudness);
      }
      else{
        mouthTime = 0;
        mouth.write(30);
        Serial.println(0);
      }
    }
    printTime = 0;
    maxLoudness = 0;
  }
}
