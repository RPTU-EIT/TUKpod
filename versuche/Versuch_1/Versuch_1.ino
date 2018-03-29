//Versuch 1
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform waveform1; //xy=500,300
AudioOutputI2S audioOut; //xy=700,300
AudioConnection patchCord1(waveform1, 0, audioOut, 0);
AudioConnection patchCord2(waveform1, 0, audioOut, 1);
AudioControlSGTL5000 audioShield; //xy=500,400
// GUItool: end automatically generated code

void setup(void)
{
	AudioMemory(8);
	audioShield.enable();
	audioShield.volume(0.6);

	waveform1.pulseWidth(0.5);
	waveform1.begin(0.4, 300, WAVEFORM_SINE);
}

void loop() {
	waveform1.frequency(300); //set frequency to 300Hz
	delay(1000);
	waveform1.frequency(600); //set frequency to 600Hz
	delay(1000);
}