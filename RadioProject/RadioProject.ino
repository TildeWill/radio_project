/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
*/

#define SOURCE_BLUETOOTH 0
#define SOURCE_FM 1

#include "MomentaryButton.h"
#include "Logger.h"

void outputFunction(String s) {
  Serial.println(s);
}

Logger logger(&outputFunction);

void callTheCallback() {
  logger.debug("Button called back");
}

MomentaryButton skipButton(2, &callTheCallback);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  
  skipButton.checkButton();
  
  delay(1);        // delay in between reads for stability
}

