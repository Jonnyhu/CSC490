#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

#define LEXMATRIX       6
#define RECV_PIN       11
#define NUMPIXELS      64
#define BRIGHTNESS     130
#define DELAYTIME      40

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEXMATRIX, NEO_GRB + NEO_KHZ800);
IRrecv irrecv(RECV_PIN);
IRsend irsend;

//------------------------------Receive---------------------
decode_results results;
int index = 0;
int i_pixel = 0;
int red, green, blue;
long unsigned int seqNum, ackNum;
boolean shake = true;

//------------------------------Send---------------------
boolean send = false;

long unsigned int data = 0xA5CA45;

void setup(){
  seqNum = random(0,16);
  pixels.begin();
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Setup Complete");
}

//------------------------------------------MAIN--------------------------------------------
void loop() {
  //handshake
  shake = handshake();
  
  while(!shake) {
    Serial.println("handshake complete");
    //receive IR signal
    decodeIR();
    //display signal
    updatePixel(i_pixel);
    
    //somesort of timeout
    //break while
  }
}

boolean handshake(){
  //0x00000000
  //Seq, 0-1st
  //RGB, 2nd - 7th
  
  //Step 1:
  do {
    //listen for signal
    decodeIR();
    data = seqNum << 28;
    
    //echo seqNum + 1 back
    sendIR(data);
    delay(random(0, DELAYTIME));
  } while (ackNum != seqNum -1 );
  
  return false;
}
  

void sendIR(long unsigned int data) {
    irsend.sendSony(data, 32);
}

void decodeIR() {
  if (irrecv.decode(&results)) {
      Serial.println(results.value, HEX);
      String ack = "0x"+String(results.value, HEX).substring(0,2);
      String R = "0x"+String(results.value, HEX).substring(2,4);
      String G = "0x"+String(results.value, HEX).substring(4,6);
      String B = "0x"+String(results.value, HEX).substring(6,8);
      ackNum = strtol(ack.c_str(), NULL, 0);
      seqNum = (seqNum+1)%16;
      red = strtol(R.c_str(), NULL, 0);
      green = strtol(G.c_str(), NULL, 0);
      blue = strtol(B.c_str(), NULL, 0);
      Serial.print("N ");
      Serial.println(ackNum);
      Serial.print("R ");
      Serial.println(red);
      Serial.print("G ");
      Serial.println(green);
      Serial.print("B ");
      Serial.println(blue);
      Serial.print("ackNum: ");
      Serial.println(ackNum);
      Serial.print("seqNum: ");
      Serial.println(seqNum);
      irrecv.resume(); // Receive the next value
  }
  Serial.println("-----------------------------------------");
}

void updatePixel(int i_pixel) {
  pixels.setPixelColor(i_pixel, pixels.Color(red, green, blue)); // Moderately bright green color.
  pixels.show(); // This sends the updated pixel color to the hardware.
  
  if (i_pixel == NUMPIXELS - 1) {
    i_pixel = 0;
  }
  else {
    i_pixel++;
  }
}
