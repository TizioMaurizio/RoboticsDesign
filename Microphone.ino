#include "SoftwareSerial.h"
#include <DFRobotDFPlayerMini.h>
#include "mic.h"

static const uint8_t TX=7;
static const uint8_t RX=8;
static const long RST=172800000;
int S =0;
int DELTA=25;
int SPR=15;
int TTH= 700;

/*
int nfiles;
int t_i =0;
int t_state=0;*/
//buttons
volatile int svol = 20;
long tdeb = 0;
long debounce = 1500;

//mic
long t =0;
long silence_threshold = 6000;
long random_threshold = 8000;
Mic mic = Mic();
long mvol=0;
long mic_th=0;


//player
SoftwareSerial ss(RX, TX);
int speech=0;

void microphoneSetup() {
  // put your setup code here, to run once:
  
  mic.dyn_th();
  mic_th = mic.mic_th;
  
  Serial.print("Threshold=");
  Serial.println(mic.mic_th);
  ss.begin(9600);
  Serial.begin(9600);
  //delay(1000);
  if(!player.begin(ss)){
    Serial.println("error player"); 
   }
  player.volume(svol);
  /*
  player.play(5);
  t=millis();
  while(millis()-t<4000){};
  player.stop();
  t=millis();*/

   /*
   nfiles = player.readFileCounts();
   Serial.println(nfiles);*/
   
   //player.play(t_i);

}

void microphoneLoop() {

  // put your main code here, to run repeatedly:

  //reset after RST time
  if(millis()>= RST){
    rst();
  }
  
  Serial.println("ecco");
  //Serial.print(mic_th);
  //Serial.print(",");
  Serial.print(TTH);
  Serial.print(",");
  //Serial.print(pow(mic_th+DELTA,2));
  //Serial.print(",");
  //Serial.print(pow(mic_th-DELTA,2));
  //Serial.print(",");
  
  
  Serial.println (abs(mic.ReadVol()));
  mvol = mic.sVol();
  if ((mic.ReadVol()>TTH)){
    speech++;
    }
  //Serial.println (mvol);
if((speech>=SPR) && ((millis()-t)> random_threshold)){//((millis()-t)> random_threshold-200) && ((millis()-t)< random_threshold+200)){
  //Serial.println (mvol);
  t=millis();
  player.play(4);
  while(millis()-t<4000){};
  player.stop();
  t=millis();
  speech=0;
  //delay(500);
 }
if((speech<SPR) && ((millis()-t)> silence_threshold)){//(millis()-t)> (silence_threshold-200) && (millis()-t)< (silence_threshold+200)){
  //Serial.println ("please speak");
  t=millis();
  player.play(2);
  while(millis()-t<4000){};
  player.stop();
  t=millis();
  speech=0;
  //delay(500);
  }
//Serial.println (mvol);
  /*
  t_state = player.readState();
  if (t_state == 513){
    //playing
    Serial.println("sono play");
  } else if (t_state == 512){
    delay(500);
    Serial.println("sono out");
    t_i++;
    if (t_i>= nfiles){
      t_i=0;
    }
    player.play(t_i);
  }*/
  /*
  player.play(t_i);
  delay(4000);
  t_i++;
  player.play(t_i);*/
/*
    player.play("001.mp3");
    delay(4000);
    player.play("002lemur.mp3");
    delay(4000);
    player.play("3.mp3");
    delay(4000);
    player.play("4-Ted.mp3");
    delay(4000);
    player.play("AAA.mp3");
    delay(4000);
    //player.play("3.mp3");
    delay(4000);*/
    /*
    player.play(1);
    delay(4000);
    player.play(2);
    delay(4000);
    player.play(3);
    delay(4000);
    player.play(4);
    delay(4000);
    player.play(5);
    delay(4000);
    player.play(3);
    delay(4000);*/

}

void rst(){
  asm volatile (" jmp 0");
}
