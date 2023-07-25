#include "MomentaryButton.h"
#include "Logger.h"
#include "FMRadio.h"
#include "Screen.h"
#include "EagleEyeJPG.h"

FMRadio fmRadio;
Logger logger;
Screen screen;

void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  logger = Logger(&outputFunction);
  
  MomentaryButton button1(2, &callTheCallback, logger);
  MomentaryButton button2(3, &callTheCallback, logger);
  MomentaryButton button3(4, &callTheCallback, logger);

  fmRadio = FMRadio(button1, button2, button3, logger);

  screen = Screen();
  screen.begin();
}

void loop() {
  screen.drawJpeg(EagleEye, sizeof(EagleEye), 0, 0);
  fmRadio.checkButtons();
  delay(100);        // delay in between reads for stability
}

void outputFunction(String s) {
  Serial.println(s);
}

void callTheCallback() {
  logger.log("Button called back");
}