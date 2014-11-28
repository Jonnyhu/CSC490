/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

IRsend irsend;

long unsigned int data = 0xA5CA45;

boolean send = false;

void setup()
{
  Serial.begin(9600);
}

void loop() {
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(data, 24); // Sony TV power code
      delay(80);
    }
    /*while (!send) {
      Serial.println("pass");
    }*/
}
