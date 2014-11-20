// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      64

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t c[] = {pixels.Color(165,202,69),
                pixels.Color(110,136,47),
                pixels.Color(192,112,58),
                pixels.Color(245,224,122),
                pixels.Color(0,0,0),
                pixels.Color(161,146,80),
                pixels.Color(109,68,32),
                pixels.Color(163,101,48),
                pixels.Color(157,157,157),
                pixels.Color(138,216,241)};

int idle1[] = {0,0,1,1,0,9,9,9,
               9,0,1,1,1,0,9,9,
               6,0,3,4,3,4,9,9,
               9,5,3,3,3,3,9,9,
               0,0,1,1,1,0,0,9,
               3,6,7,7,8,6,3,9,
               9,0,0,0,0,0,9,9,
               9,6,9,9,9,6,9,9};
                     
int idle2[] = {9,9,9,9,9,9,9,9,
               0,0,1,1,0,9,9,9,
               9,0,1,1,1,0,9,9,
               6,0,3,4,3,4,9,9,
               9,5,3,3,3,3,9,9,
               0,0,1,1,1,0,0,9,
               3,6,7,7,8,6,3,9,
               9,0,0,0,0,0,9,9};
                    
int shoot1[] = {0,0,1,1,0,9,2,9,
                9,0,1,1,1,0,9,2,
                6,0,3,4,3,4,9,2,
                3,5,3,3,3,3,9,2,
                0,0,1,1,1,0,0,3,
                9,6,7,7,8,6,9,2,
                9,0,0,0,0,0,9,2,
                9,6,9,9,9,6,2,9};

int shoot2[] = {0,0,1,1,0,9,2,9,
                9,0,1,1,1,0,9,2,
                9,0,3,4,3,4,9,2,
                9,5,3,3,6,6,6,2,
                9,0,0,3,1,0,0,3,
                9,6,7,7,8,6,9,2,
                9,0,0,0,0,0,9,2,
                9,6,9,9,9,6,2,9};

int shoot3[] = {0,0,1,1,0,9,2,9,
                9,0,1,1,1,0,9,2,
                9,0,3,4,3,4,9,2,
                9,5,3,6,6,6,6,2,
                9,0,3,1,1,0,0,3,
                9,6,7,7,8,6,9,2,
                9,0,0,0,0,0,9,2,
                9,6,9,9,9,6,2,9};

int shoot4[] = {0,0,1,1,0,9,2,9,
                9,0,1,1,1,0,9,2,
                9,0,3,4,3,4,9,2,
                9,5,6,6,6,6,6,2,
                0,3,1,1,1,0,0,3,
                9,6,7,7,8,6,9,2,
                9,0,0,0,0,0,9,2,
                9,6,9,9,9,6,2,9};

int shoot5[] = {0,0,1,1,0,9,2,9,
                9,0,1,1,1,0,9,2,
                9,0,3,4,3,4,9,2,
                3,5,3,3,6,6,6,2,
                0,0,1,1,1,0,0,3,
                9,6,7,7,8,6,9,2,
                9,0,0,0,0,0,9,2,
                9,6,9,9,9,6,2,9};
                
int shoot6[] = {0,0,1,1,0,9,2,9,
                9,0,1,1,1,0,9,2,
                9,0,3,4,3,4,9,2,
                3,5,3,3,3,3,6,2,
                0,0,1,1,1,0,0,3,
                9,6,7,7,8,6,9,2,
                9,0,0,0,0,0,9,2,
                9,6,9,9,9,6,2,9};

void setup() {
  Serial.begin(9800);
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(75);
  randomSeed(analogRead(0));
}

void loop() {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  idle();
}

void idle(){ 
  for (int i = 1; i <= 2; i++){
    int r = random(4);
    Serial.println(r);
    if (r == 0) {
      Serial.println("shoot?");
      shoot();
    }
    for (int j = 0; j < NUMPIXELS; j++){
      if (i == 1){
        pixels.setPixelColor(j, c[idle1[j]]);
      }else if (i == 2){
        pixels.setPixelColor(j, c[idle2[j]]);
      }
    }
    pixels.show();
    delay(500);
  }
}

void shoot(){
  for (int i = 1; i <= 7; i++){
    for (int j = 0; j < NUMPIXELS; j++){
      if (i == 1){
        pixels.setPixelColor(j, c[shoot1[j]]);
      }else if (i == 2){
        pixels.setPixelColor(j, c[shoot2[j]]);
      }else if (i == 3){
        pixels.setPixelColor(j, c[shoot3[j]]);
      }else if (i == 4){
        pixels.setPixelColor(j, c[shoot4[j]]);
      }else if (i == 5){
        pixels.setPixelColor(j, c[shoot5[j]]);
      }else if (i == 6){
        pixels.setPixelColor(j, c[shoot6[j]]);
      }else if (i == 7){
        pixels.setPixelColor(j, c[shoot1[j]]);
        pixels.setPixelColor(16, c[9]);
      }
    }
    if(i == 5){
      delay(800);
    }else{
      delay(300);
    }
    pixels.show();
  }
}
