#define IRpin_PIN      PIND
#define IRpin          2

#define MAXPULSE       65000

#define RESOLUTION     20

uint16_t pulses [100][2];
uint8_t currentpulse = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Ready to decode IR!");
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t highpulse, lowpulse;
  highpulse = lowpulse = 0;
  
  while (IRpin_PIN & (1 << IRpin)){
    highpulse++;
    Serial.println("high");
    delayMicroseconds(RESOLUTION);
    
    if ((highpulse >= MAXPULSE) && (currentpulse != 0)) {
      printpulses();
      currentpulse = 0;
      return;
    }
  }
  
  pulses[currentpulse][0] = highpulse;
  
  while (! (IRpin_PIN & (_BV(IRpin)))) {
    lowpulse ++;
    Serial.println("low");
    delayMicroseconds(RESOLUTION);
    if ((lowpulse >= MAXPULSE) && (currentpulse != 0)) {
      printpulses();
      currentpulse = 0;
      return;
    }
  }
  pulses[currentpulse][1] = lowpulse;
  
  currentpulse ++;
}

void printpulses(void) {
  Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
  for (uint8_t i = 0; i < currentpulse; i++) {
    Serial.print(pulses[i][0] * RESOLUTION, DEC);
    Serial.print(" usec, ");
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
    Serial.println(" usec");
  }
  
  Serial.println("int IRsignal[] = {");
  Serial.println("// ON, OFF ");
  for (uint8_t i = 0; i < currentpulse-1; i++) {
    Serial.print("pulseIR(");
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
    Serial.print(");");
    Serial.println("");
    Serial.print("delayMicroseconds(");
    Serial.print(pulses[i+1][0] * RESOLUTION, DEC);
    Serial.println(");");
  }
  
  Serial.print("pulseIR(");
  Serial.print(pulses[currentpulse-1][1] * RESOLUTION, DEC);
  Serial.print(");");
}
