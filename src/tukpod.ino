//tukpod - GNU General Public License v3.0
//https://github.com/TUK-EIT/tukpod
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            lineIn;         //xy=534,332
AudioFilterBiquad        biquadLowpassRight; //xy=772,252
AudioFilterBiquad        biquadLowpassLeft; //xy=774,216
AudioFilterBiquad        biquadHighpassLeft; //xy=774,312
AudioFilterBiquad        biquadHighpassRight; //xy=774,351
AudioFilterBiquad        biquadBandpassLeft; //xy=776,401
AudioFilterBiquad        biquadBandpassRight; //xy=776,440
AudioMixer4              mixerRight;     //xy=1009,374
AudioMixer4              mixerLeft;      //xy=1010,284
AudioOutputI2S           lineOut;        //xy=1163,328
AudioConnection          patchCord1(lineIn, 0, biquadLowpassLeft, 0);
AudioConnection          patchCord2(lineIn, 0, biquadHighpassLeft, 0);
AudioConnection          patchCord3(lineIn, 0, biquadBandpassLeft, 0);
AudioConnection          patchCord4(lineIn, 1, biquadHighpassRight, 0);
AudioConnection          patchCord5(lineIn, 1, biquadLowpassRight, 0);
AudioConnection          patchCord6(lineIn, 1, biquadHighpassRight, 0);
AudioConnection          patchCord7(lineIn, 1, biquadBandpassRight, 0);
AudioConnection          patchCord8(biquadLowpassRight, 0, mixerRight, 0);
AudioConnection          patchCord9(biquadLowpassLeft, 0, mixerLeft, 0);
AudioConnection          patchCord10(biquadHighpassLeft, 0, mixerLeft, 1);
AudioConnection          patchCord11(biquadHighpassRight, 0, mixerRight, 1);
AudioConnection          patchCord12(biquadHighpassRight, 0, mixerRight, 2);
AudioConnection          patchCord13(biquadBandpassLeft, 0, mixerLeft, 2);
AudioConnection          patchCord14(mixerRight, 0, lineOut, 1);
AudioConnection          patchCord15(mixerLeft, 0, lineOut, 0);
AudioControlSGTL5000     audioShield;    //xy=549,446
// GUItool: end automatically generated code

const int audioShieldInput = AUDIO_INPUT_LINEIN;

void setup() {
	//allocate memory (https://www.pjrc.com/teensy/td_libs_AudioConnection.html)
  AudioMemory(12);
  
  //enable the audioShield (https://www.pjrc.com/store/teensy3_audio.html)
  audioShield.enable();
  
  //select the audioShield input
  audioShield.inputSelect(audioShieldInput);
  
  //set the headphone volume(0.8 corresponds to the maximum undistorted output)
  audioShield.volume(0.6);

  /*
  https://www.pjrc.com/teensy/gui/index.html?info=AudioFilterBiquad:
  setBandpass(stage, frequency, Q);
	Configure one stage of the filter (0 to 3) with
	band pass response. The filter has unity gain
	at the specified frequency. Q controls the width
	of frequencies allowed to pass. 
  */
  biquadLowpassRight.setLowpass(0, 400, 0.700);
  biquadLowpassLeft.setLowpass(0, 400, 0.700);
  biquadHighpassRight.setHighpass(0, 5000, 0.700);
  biquadHighpassLeft.setHighpass(0, 5000, 0.700);
  biquadBandpassRight.setBandpass(0, 400, 0.100);
  biquadBandpassLeft.setBandpass(0, 400, 0.100);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
