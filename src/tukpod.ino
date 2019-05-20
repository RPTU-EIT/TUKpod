#include <FastLED.h>
#include <Audio.h>

// GUItool: begin automatically generated code
AudioInputUSB            usbIn;          //xy=120.19999694824219,129.1999969482422
AudioAnalyzePeak         peak_R;         //xy=326.20001220703125,240.1999969482422
AudioAnalyzePeak         peak_L;         //xy=328.20001220703125,203.1999969482422
AudioMixer4              mixer1;         //xy=372.20001220703125,139.1999969482422
AudioFilterBiquad        biquad1;        //xy=538.2000122070312,123.19999694824219
AudioFilterBiquad        biquad2;        //xy=538.2000122070312,163.1999969482422
AudioOutputI2S           audioOut;       //xy=698.2000122070312,143.1999969482422
AudioConnection          patchCord1(usbIn, 0, mixer1, 0);
AudioConnection          patchCord2(usbIn, 0, peak_L, 0);
AudioConnection          patchCord3(usbIn, 1, mixer1, 1);
AudioConnection          patchCord4(usbIn, 1, peak_R, 0);
AudioConnection          patchCord5(mixer1, biquad1);
AudioConnection          patchCord6(mixer1, biquad2);
AudioConnection          patchCord7(biquad1, 0, audioOut, 0);
AudioConnection          patchCord8(biquad2, 0, audioOut, 1);
AudioControlSGTL5000     audioShield;    //xy=147.1999969482422,276.20001220703125
// GUItool: end automatically generated code


#define NUM_LEDS 24
#define DATA_PIN 33

CRGB leds[NUM_LEDS];

void blueColourGradient(CRGB* arr, uint8_t hue = 171, uint8_t sat = 255 , uint8_t val = 255) {
  //creates a blue colour gradient
  for (int led = 0; led < NUM_LEDS; led++) {
    arr[led].setHSV( hue, sat, val);
    arr[led].fadeToBlackBy(12 * led);
  }
}

void rotateNeopixel(CRGB* arr) {
  //move all elements in array to the right
  CRGB tmp[NUM_LEDS];
  int next;
  for (int led = 0; led < NUM_LEDS; led++) {
    next = (led + 1) % (NUM_LEDS);
    tmp[led] = arr[next];
  }

  for (int led = 0; led < NUM_LEDS; led++) {
    arr[led] = tmp[led];
  }
}

void rotationAnimation(CRGB* arr, int T) {
  blueColourGradient(leds);
  for (int led = 0; led < NUM_LEDS; led++) {
    rotateNeopixel(arr);
    FastLED.show();
    delay(T);
    }
}

void showPeaks(CRGB* arr, float peakLeft = 0, float peakRight = 0) {
  //some array magic to visualize the stereo peaks on the neopixel ring
  int pLeft = int(peakLeft * (NUM_LEDS / 2));
  int pRight = int(peakRight * (NUM_LEDS / 2));

  //all leds are visible with reduced brightness
  for (int led = 0; led < NUM_LEDS / 2; led++) {
    arr[led].setHSV( 99 - (108 / (NUM_LEDS / 2)) * led, 220, 75);
  }
  for (int led = 0; led < NUM_LEDS / 2; led++) {
    arr[NUM_LEDS / 2 + led].setHSV(108 / (NUM_LEDS / 2)*led, 220, 75);
  }

  //increase brightness according to the peak
  for (int led = 0; led < pLeft; led++) {
    arr[led].maximizeBrightness();
    arr[led].fadeToBlackBy( 56 );
  }
  for (int led = 0; led < pRight; led++) {
    arr[NUM_LEDS - 1 - led].maximizeBrightness();
    arr[NUM_LEDS - 1 - led].fadeToBlackBy( 56 );
  }
}

void setup() {
  //audio
  AudioMemory(12);
  audioShield.enable();
  audioShield.volume(0);

  //lowpass and highpass with two biquad filters
  biquad1.setLowpass(0, 2000, 0.5);   //left signal : lowpass    (chinch: black)
  biquad2.setHighpass(0, 2000, 0.5);  //right signal : highpass  (chinch: red, white)

  //neopixel setup
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  //will show the peak animation if both peaks are available. If this isn't the case it will show the 'waiting animation'
  if (peak_L.available() && peak_R.available()) {
    showPeaks(leds, peak_L.read(), peak_R.read());
    FastLED.show();
    delay(80);
  }
  else {
    rotationAnimation(leds, 150);
  }

  //use usbIn.volume() to get the USB volume
  //recommended use: audioShield.volume(usbIn.volume()*0.7); //multiply with 0.7 to avoid distortion
  audioShield.volume(0.4); //USB volume set to 0.4 to minimize tda7376B thermanl output
}
