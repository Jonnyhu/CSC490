/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

#define LEXMATRIX       6
#define RECV_PIN       11
#define NUMPIXELS      64
#define BRIGHTNESS     130

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEXMATRIX, NEO_GRB + NEO_KHZ800);

IRrecv irrecv(RECV_PIN);

decode_results results;

int index = 0;
int i_pixel = 0;
int red, green, blue;



void setup()
{
  pixels.begin();
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Decoding IR");
}

void loop() {
  printIR();
  //delay(50);
}

void printIR() {
  if (irrecv.decode(&results)) {
      Serial.println(results.value, HEX);
      String R = "0x"+String(results.value, HEX).substring(0,2);
      String G = "0x"+String(results.value, HEX).substring(2,4);
      String B = "0x"+String(results.value, HEX).substring(4,6);
      red = strtol(R.c_str(), NULL, 0);
      green = strtol(G.c_str(), NULL, 0);
      blue = strtol(B.c_str(), NULL, 0);
      Serial.print("R ");
      Serial.println(red);
      Serial.print("G ");
      Serial.println(green);
      Serial.print("B ");
      Serial.println(blue);
      irrecv.resume(); // Receive the next value
  }
  Serial.println("-----------------------------------------");

  pixels.setPixelColor(i_pixel, pixels.Color(red, green, blue)); // Moderately bright green color.
  pixels.show(); // This sends the updated pixel color to the hardware.
  
  if (i_pixel == NUMPIXELS - 1) {
    i_pixel = 0;
  }
  else {
    i_pixel++;
  }
}
