#ifndef Screen_h
#define Screen_h
#include "Arduino.h" 
#include <TFT_eSPI.h>
#include "ScrollableSprite.h"

class Screen: public TFT_eSPI {
public:
  Screen();
  void begin();
  void drawJpeg(const uint8_t arrayname[], uint32_t array_size, int xpos, int ypos);
  void wipeScreen();
  void setTitle(String title);
  void scrollTitle();
  void setArtist(String artist);
  void scrollArtist();
  void debug(String message);
private:
  ScrollableSprite* titleSprite;
  ScrollableSprite* artistSprite;
  void renderJPEG(int xpos, int ypos);
  
  int scrollCounter;
  int spriteWidth;
  int scrollAmount;
  int titleHeight;
  int titleFontSizeMultiplier;
  int titleFontType;
  int bufferBetweenText;
};

#endif