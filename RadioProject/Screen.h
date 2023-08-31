#ifndef Screen_h
#define Screen_h
#include "Arduino.h" 
#include <TFT_eSPI.h>

class Screen {
public:
  Screen(TFT_eSPI* tft, TFT_eSprite* sprite);
  void begin();
  void drawJpeg(const uint8_t arrayname[], uint32_t array_size, int xpos, int ypos);
  void wipeScreen();
  void setTitle(String title);
  void scrollTitle();
  void debug(String message);
private:
  TFT_eSPI* tft; 
  TFT_eSprite* sprite;
  void renderJPEG(int xpos, int ypos);
  String title;
  
  int scrollCounter;
  int spriteWidth;
  int scrollAmount;
  int titleHeight;
  int titleFontSizeMultiplier;
  int titleFontType;
  int bufferBetweenText;
};



#endif