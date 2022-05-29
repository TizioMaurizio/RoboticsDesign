long t = 0;
long debounce = 500;
//DFRobotDFPlayerMini player;
//volatile int volume = 15;

void volumeButtonsSetup() {
  // put your setup code here, to run once:

  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), vol_up, RISING);
  attachInterrupt(digitalPinToInterrupt(2), vol_down, RISING);
  player.volume(volume);
}


void volumeButtonsLoop(){
  //Serial.print(volume);
  //Serial.print(",");
  /*
  volumeUpState = digitalRead(volumeUpPin);
  volumeDownState = digitalRead(volumeDownPin);

  if (volumeUpState){
    volumeUpPressed = true;
  }
  if (volumeDownState){
    volumeDownPressed = true;
  }

  if ((volumeUpPressed) and !(volumeUpState)){
    volumeUpPressed = false;
    if (volume < 30)
      volume ++;
    player.volume(volume);
    //TODO playJoke(/*AAAAAA);
  }
  if ((volumeDownPressed) and !(volumeDownState)){
    volumeDownPressed = false;
    if(volume > 0)
      volume --;
    player.volume(volume);
    //playJoke(/*AAAAAA);
  }*/
}


void vol_up(){
  if((millis()-t)>debounce){
    if (volume < 30)
      volume += 3;
    player.volume(volume);
    Serial.println("AAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    t = millis();
  }
}

void vol_down(){
  if((millis()-t)>debounce){
    if(volume > 0)
      volume -= 3;
    player.volume(volume);
    Serial.println("BBBBBBBBBBBBBBBBBBBBBBBBBBBB");
    t=millis();
  }
}
