/*
To upload code when the serial port is busy and the port is flip-flopping between being available and not:
1. Connect the board via the USB cable (no need to disconnect and reconnect)
2. Press and hold the BOOT button (white, left of the USB port), 
3. While still pressing the BOOT button, press RST (side, black button)
4. Release the RST
5. Release the BOOT button - this boots the board into an idle state, but you can't upload, so...
6. Press and release the BOOT button again
7. Upload your sketch

Also bought a cable directly from Arduino
Also installed new drivers on my Mac per the instructions here https://mim-armand.medium.com/esp32-upload-problem-on-mac-os-ae5318358ad6 and used 
/dev/cu/wchusbserial56570278231 as my port instead of the non-"wch" port

Reference: https://github.com/Xinyuan-LilyGO/T-Display-S3/issues/111

Upload speed seems to have to be 115200 or slower
*/
#include <TFT_eSPI.h>

#include "MomentaryButton.h"
#include "Logger.h"
#include "Receiver.h"
#include "FMRadio.h"
#include "BluetoothReceiver.h"
#include "Screen.h"
#include "AlbumImage.h"


Receiver* receiver;
FMRadio fmRadio;
BluetoothReceiver bluetoothReceiver;
Logger logger;

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft); 
Screen  screen = Screen(&tft, &sprite);
 
int albumDelay = 1000; //1 second
long int albumGoTime;

int buttonDelay = 100;
long int buttonGoTime;

int scrollDelay = 10; 
long int titleScrollTime;

void avrc_metadata_callback(uint8_t attributeId, const uint8_t* buffer) {
  Serial.printf("AVRC metadata rsp: attribute id 0x%x, %s\n", attributeId, buffer);
  if(attributeId == ESP_AVRC_MD_ATTR_TITLE) {
    String str = (char*)buffer;
    screen.setTitle((String)str);
  }
}

void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  
  albumGoTime = millis();
  buttonGoTime = millis();

  logger = Logger(&outputFunction);
  
  MomentaryButton button1(2, &callTheCallback, logger);
  MomentaryButton button2(3, &callTheCallback, logger);
  MomentaryButton button3(4, &callTheCallback, logger);

  
  screen.begin();

  fmRadio = FMRadio(button1, button2, button3, logger);
  bluetoothReceiver = BluetoothReceiver(button1, button2, button3, logger, avrc_metadata_callback);
  receiver = &fmRadio;
  // screen.setTitle("Twenty Two - Taylor Swift");
  screen.debug("(Skip)");
}

void loop() {
  
  if(millis() >= albumGoTime) {
    screen.drawJpeg(AlbumImage, sizeof(AlbumImage), 0, 0);
    albumGoTime = millis() + albumDelay; 
  }

  if(millis() >= buttonGoTime) {
    receiver->checkButtons();
    buttonGoTime = millis() + buttonDelay; 
  }

  if(millis() >= titleScrollTime) {
    screen.scrollTitle();
    titleScrollTime = millis() + scrollDelay; 
  }

}

void outputFunction(String s) {
  Serial.println(s);
}

void callTheCallback() {
  logger.log("Button called back");
}