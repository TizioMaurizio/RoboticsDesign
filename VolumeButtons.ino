const int volumeUpPin = 8;
const int volumeDownPin =  9;
bool volumeUpPressed = false;
bool volumeDownPressed = false;
int volumeUpState = 0;
int volumeDownState = 0;
//DFRobotDFPlayerMini player;
//int volume = 15;

void volumeButtonsSetup(){
  pinMode(volumeUpPin, INPUT);
  pinMode(volumeUpPin, INPUT);
}

void volumeButtonsLoop(){
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
    //TODO playJoke(/*AAAAAA*/);
  }
  if ((volumeDownPressed) and !(volumeDownState)){
    volumeDownPressed = false;
    if(volume > 0)
      volume --;
    player.volume(volume);
    //playJoke(/*AAAAAA*/);
  }
}
