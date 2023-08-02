/*
To upload code when the serial port is busy and the port is flip-flopping between being available and not:
1. Connect the board via the USB cable (no need to disconnect and reconnect)
2. Press and hold the BOOT button (white, left of the USB port), 
3. While still pressing the BOOT button, press RST (side, black button)
4. Release the RST
5. Release the BOOT button - this boots the board into an idle state, but you can't upload, so...
6. Press the BOOT button again
7. Upload your sketch

Reference: https://github.com/Xinyuan-LilyGO/T-Display-S3/issues/111

Upload speed seems to have to be 115200 or slower
*/

#include "MomentaryButton.h"
#include "Logger.h"
#include "Receiver.h"
#include "FMRadio.h"
#include "BluetoothReceiver.h"
#include "Screen.h"
#include "EagleEyeJPG.h"


Receiver* receiver;
FMRadio fmRadio;
BluetoothReceiver bluetoothReceiver;
Logger logger;
Screen screen;

void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  logger = Logger(&outputFunction);
  
  MomentaryButton button1(2, &callTheCallback, logger);
  MomentaryButton button2(3, &callTheCallback, logger);
  MomentaryButton button3(4, &callTheCallback, logger);

  screen = Screen();
  screen.begin();

  fmRadio = FMRadio(button1, button2, button3, logger);
  bluetoothReceiver = BluetoothReceiver(button1, button2, button3, logger);
  receiver = &fmRadio;
}

void loop() {
  screen.drawJpeg(EagleEye, sizeof(EagleEye), 0, 0);
  receiver->checkButtons();
  delay(100);        // delay in between reads for stability
}

void outputFunction(String s) {
  Serial.println(s);
}

void callTheCallback() {
  logger.log("Button called back");
}