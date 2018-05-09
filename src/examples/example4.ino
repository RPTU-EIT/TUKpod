//example 4
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            lineIn;           //xy=336,301
AudioFilterBiquad        biquadLowpassRight; //xy=592,225
AudioFilterBiquad        biquadLowpassLeft; //xy=594,189
AudioFilterBiquad        biquadHighpassLeft; //xy=594,285
AudioFilterBiquad        biquadHighpassRight; //xy=594,324
AudioFilterBiquad        biquadBandpassLeft; //xy=596,374
AudioFilterBiquad        biquadBandpassRight; //xy=596,413
AudioMixer4              mixerRight;     //xy=829,347
AudioMixer4              mixerLeft;      //xy=830,257
AudioOutputI2S           lineOut;        //xy=983,301
AudioConnection          patchCord1(lineIn, 0, biquadLowpassLeft, 0);
AudioConnection          patchCord2(lineIn, 0, biquadHighpassLeft, 0);
AudioConnection          patchCord3(lineIn, 0, biquadBandpassLeft, 0);
AudioConnection          patchCord4(lineIn, 1, biquadLowpassRight, 0);
AudioConnection          patchCord5(lineIn, 1, biquadHighpassRight, 0);
AudioConnection          patchCord6(lineIn, 1, biquadBandpassRight, 0);
AudioConnection          patchCord7(biquadLowpassRight, 0, mixerRight, 0);
AudioConnection          patchCord8(biquadLowpassLeft, 0, mixerLeft, 0);
AudioConnection          patchCord9(biquadHighpassLeft, 0, mixerLeft, 1);
AudioConnection          patchCord10(biquadHighpassRight, 0, mixerRight, 1);
AudioConnection          patchCord11(biquadBandpassLeft, 0, mixerLeft, 2);
AudioConnection          patchCord12(biquadBandpassRight, 0, mixerRight, 2);
AudioConnection          patchCord13(mixerRight, 0, lineOut, 1);
AudioConnection          patchCord14(mixerLeft, 0, lineOut, 0);
AudioControlSGTL5000     audioShield;    //xy=351.,461
// GUItool: end automatically generated code

const int myInput = AUDIO_INPUT_LINEIN; // AUDIO_INPUT_MIC;

void setup() {
	AudioMemory(12);

	audioShield.enable();
	audioShield.inputSelect(myInput);
	audioShield.volume(0.6);

	biquadLowpassRight.setLowpass(0, 400, 0.700);
	biquadLowpassLeft.setLowpass(0, 400, 0.700);
	biquadHighpassRight.setHighpass(0, 5000, 0.700);
	biquadHighpassLeft.setHighpass(0, 5000, 0.700);
	biquadBandpassRight.setBandpass(2, 400, 0.100);
	biquadBandpassLeft.setBandpass(2, 400, 0.100);
}

void loop() {
	delay(100);
}
