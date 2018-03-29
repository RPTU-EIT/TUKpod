//Versuch 5.1
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S lineIn; //xy=345,223
AudioMixer4 mixer1; //xy=583,127
AudioOutputI2S audioOut; //xy=598,221
AudioAnalyzePeak peak1; //xy=747,122
AudioConnection patchCord1(lineIn, 0, audioOut, 0);
AudioConnection patchCord2(lineIn, 0, mixer1, 0);
AudioConnection patchCord3(lineIn, 1, audioOut, 1);
AudioConnection patchCord4(lineIn, 1, mixer1, 3);
AudioConnection patchCord5(mixer1, peak1);
AudioControlSGTL5000 audioShield; //xy=345,263
// GUItool: end automatically generated code

//vars
int leds[] = {A13, A14, A15, A16, A17, A18, A19, A20, A21, A22};
const int ledAnzahl = 10;
const int inputSource = AUDIO_INPUT_LINEIN; //AUDIO_INPUT_MIC;

//function
void setPeak (int);

void setup(){
	int i;
	
	AudioMemory(12);
	
	audioShield.enable();
	audioShield.inputSelect(inputSource);
	audioShield.volume(0.60);
	
	for (i=0; i<ledAnzahl; i++){
		pinMode(leds[i], OUTPUT);
	}
}

void loop() {
	if (peak1.available()){
		int monoPeak = (int) (peak1.read()*10.0);
		setPeak(monoPeak);
	}
	delay(75); //fps 50
}

void setPeak (int level){
	int i;
	if (level<=ledAnzahl && level>=0){ //check because ledAnzahl and leds[] can be changed by the user
		for (i=0; i<ledAnzahl; i++){
			if (i<=level){
				analogWrite(leds[i], 255);
			}
			else{
				analogWrite(leds[i], 0);
			}
		}
	}
}