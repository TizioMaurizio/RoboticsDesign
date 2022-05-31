//long buttonTime = 0;
long buttonDebounce = 500;
//DFRobotDFPlayerMini player;
//volatile int volume = 15;
int volumeUpState =0;
int volumeDownState =0;
bool volumeUpPressed;
bool volumeDownPressed;
int volumeUpPin = 3;
int volumeDownPin = 2;

void volumeButtonsSetup(){
  // put your setup code here, to run once:

  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  
  //attachInterrupt(digitalPinToInterrupt(3), vol_up, RISING);
  //attachInterrupt(digitalPinToInterrupt(2), vol_down, RISING);
  player.volume(volume);
}


void volumeButtonsLoop(){
  //Serial.print(volume);
  //Serial.print(",");
  
  volumeUpState = digitalRead(volumeUpPin);
  volumeDownState = digitalRead(volumeDownPin);

  if (volumeUpState){
    volumeUpPressed = true;
  }
  if (volumeDownState){
    volumeDownPressed = true;
  }

  if ((volumeUpPressed) and !(volumeUpState) and (millis()-t)>buttonDebounce){
    volumeUpPressed = false;
    if (volume < 30)
      volume +=3;
    player.volume(volume);
    player.play(5);
    t=millis();
    //TODO playJoke(/*AAAAAA);
  }
  if ((volumeDownPressed) and !(volumeDownState) and (millis()-t)>buttonDebounce){
    volumeDownPressed = false;
    if(volume > 0)
      volume -=3;
    player.volume(volume);
    player.play(5);
    t=millis();
    //playJoke(/*AAAAAA);
  }
}

/*
void vol_up(){
  if((millis()-buttonTime)>buttonDebounce){
    if (volume < 30)
      volume += 3;
    player.volume(volume);
    Serial.println("AAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    buttonTime = millis();
  }
}

void vol_down(){
  if((millis()-buttonTime)>buttonDebounce){
    if(volume > 0)
      volume -= 3;
    player.volume(volume);
    Serial.println("BBBBBBBBBBBBBBBBBBBBBBBBBBBB");
    buttonTime=millis();
  }
}*/



/*long buttonTime = 0;
long buttonDebounce = 500;
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
  //Serial.print(",");*/
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
//}

/*
void vol_up(){
  if((millis()-buttonTime)>buttonDebounce){
    if (volume < 30)
      volume += 3;
    player.volume(volume);
    Serial.println("AAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    buttonTime = millis();
  }
}

void vol_down(){
  if((millis()-buttonTime)>buttonDebounce){
    if(volume > 0)
      volume -= 3;
    player.volume(volume);
    Serial.println("BBBBBBBBBBBBBBBBBBBBBBBBBBBB");
    buttonTime=millis();
  }
}*/
