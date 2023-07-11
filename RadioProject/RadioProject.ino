#include "MomentaryButton.h"
#include "Logger.h"
#include "FMRadio.h"

FMRadio* fmRadio;
Logger* logger;

void setup() {
  logger = new Logger(&outputFunction);
  MomentaryButton button1(2, &callTheCallback, logger);
  MomentaryButton button2(3, &callTheCallback, logger);
  MomentaryButton button3(4, &callTheCallback, logger);

  fmRadio = new FMRadio(&button1, &button2, &button3, logger);
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
}

void loop() {
  fmRadio->checkButtons();
  delay(1);        // delay in between reads for stability
}

void outputFunction(String s) {
  Serial.println(s);
}

void callTheCallback() {
  logger->log("Button called back");
}