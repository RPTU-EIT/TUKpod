//example 3
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S lineIn; //xy=204,157
AudioFilterBiquad biquad1; //xy=363,136
AudioFilterBiquad biquad2; //xy=363,174
AudioOutputI2S lineOut; //xy=521,157
AudioConnection patchCord1(lineIn, 0, biquad1, 0);
AudioConnection patchCord2(lineIn, 1, biquad2, 0);
AudioConnection patchCord3(biquad1, 0, lineOut, 0);
AudioConnection patchCord4(biquad2, 0, lineOut, 1);
AudioControlSGTL5000 audioShield; //xy=215,217
// GUItool: end automatically generated code

const int myInput = AUDIO_INPUT_LINEIN; // AUDIO_INPUT_MIC;

void setup() {
	AudioMemory(12);

	audioShield.enable();
	audioShield.inputSelect(myInput);
	audioShield.volume(0.6);

	biquad1.setLowpass(0, 400, 0.707);
	biquad2.setLowpass(0, 400, 0.707);
}

void loop() {
	delay(100);
}
