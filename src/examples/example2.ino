//example 2
//Caution: set Tools/USB Type/Audio !

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputUSB            usbIn;           //xy=488,247
AudioOutputI2S           audioOut;       //xy=648,247
AudioConnection          patchCord1(usbIn, 0, audioOut, 0);
AudioConnection          patchCord2(usbIn, 1, audioOut, 1);
AudioControlSGTL5000     audioShield;    //xy=501,286
// GUItool: end automatically generated code


int volumePin = A12;    //analog pin 12
float maxVolume = 0.7;  //I do not recommend 0.8 .

void setup() {
  AudioMemory(12);
  audioShield.enable();
  audioShield.volume(0);
  pinMode(volumePin, INPUT);
}

float vol;

void loop() {
  //read analog value from poti
  vol = analogRead(volumePin);    //The PC volume does not change the teensy volume.
                                  //Use vol = usbIn.volume(); instead of vol = analogRead(volumePin);
                                  //usbIn.volume() should give you a value between 0 and 1
  //sets the volume to a range between 0 and 1023
  vol = constrain(vol, 0, 1023);
  //transform it to a range between 0 and maxVolume
  vol = (vol/1023)*maxVolume;

  //set volume
  audioShield.volume(vol);
  delay(20);
}
