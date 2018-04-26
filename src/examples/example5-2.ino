//example 5.2
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            lineIn;         //xy=533,307
AudioAnalyzePeak         peakLeft;          //xy=767,228
AudioAnalyzePeak         peakRight;          //xy=771,266
AudioOutputI2S           audioOut;       //xy=772,307
AudioConnection          patchCord1(lineIn, 0, audioOut, 0);
AudioConnection          patchCord2(lineIn, 0, peakLeft, 0);
AudioConnection          patchCord3(lineIn, 1, audioOut, 1);
AudioConnection          patchCord4(lineIn, 1, peakRight, 0);
AudioControlSGTL5000     audioShield;    //xy=548,368
// GUItool: end automatically generated code

float peakMultiplier = 160.0;
int peakHeight = 20;
const int inputSource = AUDIO_INPUT_LINEIN;

void setPeak (int, int);
void showCalibratingMessage(int, int);
void adjustGain(void);

void setup(){
  AudioMemory(12);
  Serial.begin(9600);
  audioShield.enable();
  audioShield.inputSelect(inputSource);
  audioShield.volume(0.60);

  showCalibratingMessage(peakHeight, 10);  //sec
}

void loop() {
  //audio meter
  int left = 0, right = 0;
  if(peakLeft.available() && peakRight.available()){
    left=peakLeft.read() * peakMultiplier;
    right=peakRight.read() * peakMultiplier;
  }
  
  setPeak(left, right);
  adjustGain();
  
  delay(40);
}

void setPeak (int peakLeft, int peakRight){
  //printing a audio meter to the serial connection
  int x;
  Serial.println();
  Serial.println("----------");
  for(x = peakHeight; x >= 0; x--){
    Serial.println("|  "+(String)((x >= peakLeft)?" ":"o")+"  "+(String)((x >= peakRight)?" ":"o")+"  |");
  }
  Serial.println("----------");
  Serial.println("|  L  R  | Gain: " + (String)peakMultiplier + "  increase: +  decrease: -");
  Serial.println("----------");
}

void adjustGain(void){
  //adjustGain uses the global variable peakMultiplier
  //read Serial
  if (Serial.available()){
    char data = Serial.read();
    
    //increase
    if(data == '+'){
      peakMultiplier += 1.0;
    }
    //decrease
    else if(data == '-'){
      if(peakMultiplier > 0)
        peakMultiplier -= 1.0; 
    }
  }  
}

void showCalibratingMessage(int peakHeight, int timer){
  //shows calibrating instructions
  int x, y;
  for(x = timer; x >= 0; x--){
    Serial.println();
    Serial.println("Please calibrate your window height to match the bottom line. Waiting " + (String)x + "s." );
    Serial.println("----------");
    for(y = 0; y <= peakHeight+1; y++)
      Serial.println("|        |");
    Serial.println("----------");
    delay(1000);
  }
}
