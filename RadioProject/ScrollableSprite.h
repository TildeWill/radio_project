#ifndef ScrollableSprite_h
#define ScrollableSprite_h
#include "Arduino.h" 
#include <TFT_eSPI.h>

class ScrollableSprite: public TFT_eSprite {
public:
  ScrollableSprite(TFT_eSPI* tft, int visibleWidth, int xPosition, int yPosition);
  void begin();
  void setText(String text);
  void scrollText();
  
private:
  TFT_eSPI* tft;
  int visibleWidth;
  String text;
  
  int xPosition;
  int yPosition;
  int scrollCounter;
  int spriteWidth;
  int scrollAmount;
  int textHeight;
  int fontSizeMultiplier;
  int fontType;
  int bufferBetweenText;
};

#endif