#include "MomentaryButton.h"
#include "Logger.h"

MomentaryButton* skipButton;
Logger* logger;

void setup() {
  logger = new Logger(&outputFunction);
  skipButton = new MomentaryButton(2, &callTheCallback, logger);
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
}

void loop() {
  
  skipButton->checkButton();
  
  delay(1);        // delay in between reads for stability
}

void outputFunction(String s) {
  Serial.println(s);
}

void callTheCallback() {
  logger->log("Button called back");
}