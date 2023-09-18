#ifndef ScrollableSprite_h
#define ScrollableSprite_h
#include "Arduino.h" 
#include <TFT_eSPI.h>

class ScrollableSprite {
public:
  ScrollableSprite();
  ScrollableSprite(TFT_eSprite* sprite, int visibleWidth, int xPosition, int yPosition);
  void begin();
  void setText(String text);
  void scrollText();
  
private:
  TFT_eSprite* sprite;
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