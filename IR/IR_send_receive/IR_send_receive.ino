//define pins. I used pins 4 and 5
#define irLedPin 13          // IR Led on this pin
#define irSensorPin 2       // IR sensor on this pin
#define delaytime 1000

int irRead(int readPin, int triggerPin); //function prototype
int array[5] = {1, 0, 1, 1, 0};

void setup()
{
  pinMode(irSensorPin, INPUT);
  pinMode(irLedPin, OUTPUT);
  Serial.begin(9600); 
  // prints title with ending line break 
  Serial.println("Program Starting"); 
  // wait for the long string to be sent 
  delay(100); 
}

void loop()
{  
  //Serial.println(irRead(irSensorPin, irLedPin)); //display the results
  for (int i=0; i < 5; i++){
    if (array[i] != 0) {
      irSend(irLedPin);
    }
  }
  //Serial.println(irRead(irSensorPin));
  //delay(10); //wait for the string to be sent
}
//
/******************************************************************************
 * This function can be used with a panasonic pna4602m ir sensor
 * it returns a zero if something is detected by the sensor, and a 1 otherwise
 * The function bit bangs a 38.5khZ waveform to an IR led connected to the
 * triggerPin for 1 millisecond, and then reads the IR sensor pin to see if
 * the reflected IR has been detected
 for (i=0; i <=cycles; i++)
  {
    digitalWrite(triggerPin, HIGH); 
    delayMicroseconds(halfPeriod);
    digitalWrite(triggerPin, LOW); 
    delayMicroseconds(halfPeriod - 1);     // - 1 to make up for digitaWrite overhead    
  }
 ******************************************************************************/
int irRead(int readPin)
{
  return digitalRead(readPin);
}

void irSend(int triggerPin)
{
  digitalWrite(triggerPin, HIGH);
  delay(1000);
}
