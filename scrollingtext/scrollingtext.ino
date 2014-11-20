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

String text = "SPAAAACE!!!";
int delayval = 80; // delay for half a second
int topRowIndex = 0; // range 0-3
int brightness = 50; // range 0-255
uint32_t fontColor = pixels.Color(0,0,255);

int fontsize = 5;
String msg = "";

void setup() {
  Serial.begin(9800);
  randomSeed(analogRead(0));
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(brightness);
}

void loop() {
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  scrollMsg(text, fontColor);
}

void convertChar(char c) {
  Serial.println(c);
  switch(c){
    case 'A':
      msg = "1111110100101001010011111";
      break;
    case 'B':
      msg = "1111110101101011010101110";
      break;
    case 'C':
      msg = "1111110001100011000110001";
      break;
    case 'D':
      msg = "1111110001100011000101110";
      break;
    case 'E':
      msg = "1111110101101011010110001";
      break;
    case 'F':
      msg = "1111110100101001010010000";
      break;
    case 'G':
      msg = "1111110001101011010110111";
      break;
    case 'H':
      msg = "1111100100001000010011111";
      break;
    case 'I':
      msg = "1000110001111111000110001";
      break;
    case 'J':
      msg = "10011100011111110000";
      break;
    case 'K':
      msg = "11111001000101010001";
      break;
    case 'L':
      msg = "11111000010000100001";
      break;
    case 'M':
      msg = "1111101000001000100011111";
      break;
    case 'N':
      msg = "1111101000001000001011111";
      break;
    case 'O':
      msg = "1111110001100011000111111";
      break;
    case 'P':
      msg = "1111110100101001010011100";
      break;
    case 'Q':
      msg = "1111110001100011001111111";
      break;
    case 'R':
      msg = "1111110100101001011011101";
      break;
    case 'S':
      msg = "1110110101101011010110111";
      break;
    case 'T':
      msg = "1000010000111111000010000";
      break;
    case 'U':
      msg = "1111100001000010000111111";
      break;
    case 'V':
      msg = "1100000110000010011011000";
      break;
    case 'W':
      msg = "1111100010001000001011111";
      break;
    case 'X':
      msg = "1000101010001000101010001";
      break;
    case 'Y':
      msg = "1000001000001110100010000";
      break;
    case 'Z':
      msg = "1000110011101011100110001";
      break;
    case '0':
      msg = "0111010001100011000101110";
      break;
    case '1':
      msg = "1000011111";
      break;
    case '2':
      msg = "01001100111010101001";
      break;
    case '3':
      msg = "100011010101010";
      break;
    case '4':
      msg = "11100001000010011111";
      break;
    case '5':
      msg = "11101101011010110011";
      break;
    case '6':
      msg = "11111101011010110111";
      break;
    case '7':
      msg = "10001100101010011000";
      break;
    case '8':
      msg = "11011101011010111011";
      break;
    case '9':
      msg = "11101101011010111111";
      break;
    case ',':
      msg = "0000100010";
      break;
    case '.':
      msg = "00001";
      break;
    case '?':
      msg = "0100010000101011010001000";
      break;
    case '!':
      msg = "11101";
      break;
    case ':':
      msg = "01010";
      break;
    case '(':
      msg = "0111010001";
      break;
    case ')':
      msg = "1000101110";
      break;
    case '=':
      msg = "010100101001010";
      break;
    case ' ':
      msg = "00000";
      break;
  }
  msg += "00000";
}

void scrollMsg(String s, uint32_t c){
  int i;
  int j;
  int r;
  int pixelCount;
  int numOfCol;
  s.toUpperCase();
  topRowIndex = random(4);
  for (j = 0; j < s.length(); j++){
    pixelCount = 0;
    convertChar(s[j]);
    if (j == (s.length()-1)){
      for (i = 0; i < 8; i++){
        if (fontsize == 4){
          msg += "0000";
        }else{
          msg += "00000";
        }
      }
    }
    numOfCol = msg.length()/fontsize;
    for (i = 0; i < numOfCol; i++){
      if (i != 0 || j > 0){
        shiftLeft();
      }
      for (r = 0; r < 8; r++){
        if(r < topRowIndex || r >= topRowIndex+fontsize){
          pixels.setPixelColor((r*8)+7, pixels.Color(0,0,0));
        }else{
          if(msg[pixelCount] == '1'){
            pixels.setPixelColor((r*8)+7, c);
          }else{
            pixels.setPixelColor((r*8)+7, pixels.Color(0,0,0));
          }
          pixelCount ++;
        }
      }
      pixels.show();
      delay(delayval);
    }
  }
}

void shiftLeft(){
  for (int i = 0; i < NUMPIXELS; i++){
    if (i == 0 || ((i+1)%8) != 0){
      pixels.setPixelColor(i, pixels.getPixelColor(i+1));
    }
  }
}
