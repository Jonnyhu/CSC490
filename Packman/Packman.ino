// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6

#define Row            8

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      64

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second
int packman_close[64] = {0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0};
int packman_open[64] = {0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,1,1,0,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0};
int packmanColor[64] = {};

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void playFrame(){
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,packman_open[i]*20,0)); // Moderately bright green color.
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayval);
  for(int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(0, packman_close[i]*20, 0));
  }
  pixels.show();
  delay(delayval);
}

void scroll(){
  int seperator = 0;
  int tmp1[8];
  int tmp2[8];
  for (int i=0; i<8; i++){
    tmp1[i] = packman_open[7+i*8];
    tmp2[i] = packman_close[7+i*8];
  }
  for (int i=0; i<NUMPIXELS; i++){
  }
}

void loop() {
  playframe();
  
}
