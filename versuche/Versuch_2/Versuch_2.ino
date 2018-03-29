//Versuch 2
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S lineIn; //xy=830
AudioOutputI2S audioOut; //xy=980
AudioConnection patchCord1(lineIn, 0, audioOut, 0);
AudioConnection patchCord2(lineIn, 1, audioOut, 1);
AudioControlSGTL5000 audioShield; //xy=830,40
// GUItool: end automatically generated code

const int inputSource = AUDIO_INPUT_LINEIN; //AUDIO_INPUT_MIC;

void setup() {
	AudioMemory(12);

	audioShield.enable();
	audioShield.inputSelect(inputSource);
	audioShield.volume(0.5);
}

void loop() {
	delay(100);
}