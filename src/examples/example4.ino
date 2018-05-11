//example 4
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            lineIn;         //xy=185,291
AudioMixer4              mixer;         //xy=332,304
AudioFilterBiquad        biquadHighpass; //xy=545,284
AudioFilterBiquad        biquadLowpass; //xy=546,324
AudioOutputI2S           lineOut;        //xy=759,306
AudioConnection          patchCord1(lineIn, 0, mixer, 0);
AudioConnection          patchCord2(lineIn, 1, mixer, 1);
AudioConnection          patchCord3(mixer, biquadLowpass);
AudioConnection          patchCord4(mixer, biquadHighpass);
AudioConnection          patchCord5(biquadHighpass, 0, lineOut, 0);
AudioConnection          patchCord6(biquadLowpass, 0, lineOut, 1);
AudioControlSGTL5000     audioShield;    //xy=200,381
// GUItool: end automatically generated code

const int inputSource = AUDIO_INPUT_LINEIN; // AUDIO_INPUT_MIC;

void setup() {
	AudioMemory(12);

	audioShield.enable();
	audioShield.inputSelect(inputSource);
	audioShield.volume(0.6);

	biquadLowpass.setLowpass(0, 1500, 0.700);
	biquadHighpass.setHighpass(0, 1500, 0.700);
}

void loop() {
	delay(100);
}
