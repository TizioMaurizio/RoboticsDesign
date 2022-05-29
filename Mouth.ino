#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Servo.h> 

// MP3 and motors
static const uint8_t PIN_MP3_TX = 7; // Connects to module's RX (giallo?)
static const uint8_t PIN_MP3_RX = 8; // Connects to module's TX (verde?)
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
int mouthPin = 5;
Servo mouth;
//DFRobotDFPlayerMini player; //pin to 3.3v
int mouthTime_reset = 10; //cooldown for closing mouth
int speakerPin = A1;
int maxMouthAngle = 30;

//int volume = 15;
//String joke = "";

//Move and talk///////////////////////////
int vol=0;
int i = 0;
int k = 0;
int printTime = 0;
int mouthTime = 0;
int maxLoudness = 0;
int servoAngle = 0;
int targetAngle = 0;
int threshold = 300;
int openMouth = 0;
bool closing = false;
int prevTime = 0;
bool speaking = false;

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
  int currTime = millis();
  if(Serial.available()){
    player.next();
    Serial.read();
    Serial.println("Next sound");
  }
  int analogValue = analogRead(speakerPin);
  int loudness = abs((analogValue-512)*(analogValue-512));// 3.3V: -340, 5V: -512
  
  //if((loudness<10000)&&(loudness>-10000)){
    maxLoudness = max(maxLoudness, loudness);
  //}
  //Serial.println(loudness);
  //Serial.print(threshold);
  //Serial.print(",");
  if(loudness < 50000){
    //Serial.print(volume*100);
    //Serial.print(",");
    //Serial.print(analogValue);
    //Serial.print(",");
    Serial.print(loudness);
    Serial.print(",");
    Serial.println(threshold * pow(2,(volume - 15) /3));
  }
  if(loudness>threshold * pow(2,(volume - 15) /3)){
  //if(analogValue<600){
    speaking = true;
  }
  if(currTime - prevTime >= 100){
    if(speaking){
      if(closing == false){
        mouth.write(85-maxMouthAngle);
        closing = true;
       }
      else 
        if(closing == true){
          mouth.write(85);
          closing = false;
         }
    }
    else
      mouth.write(85);
    prevTime = currTime;
    speaking = false;
  }
}
     
  
  /*
  if(printTime >= 9){ //every 9 times this is called (loop time + 1ms)
    if((maxLoudness>threshold)&&(mouthTime == 0)){//TODO and MP3BUSY
      mouth.write(90-maxMouthAngle);
      //TODO maybe also nod with neck for more mouth movement?
      mouthTime = mouthTime_reset;
      //Serial.println(maxLoudness);
    }
    else{
      if(mouthTime >= 10){
        mouthTime -= 10;
        //Serial.println(maxLoudness);
      }
      else{
        mouthTime = 0;
        mouth.write(90);
        //Serial.println(maxLoudness);
      }
    }
    printTime = 0;
    maxLoudness = 0;
  }
  
  
}*/
