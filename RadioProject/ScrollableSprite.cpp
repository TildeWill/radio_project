#include <TFT_eSPI.h>

#include "ScrollableSprite.h"

ScrollableSprite::ScrollableSprite() {}

ScrollableSprite::ScrollableSprite(TFT_eSprite* sprite, int visibleWidth, int xPosition, int yPosition) : 
  sprite(sprite), visibleWidth(visibleWidth), xPosition(xPosition), yPosition(yPosition) {}

void ScrollableSprite::begin() {
  scrollCounter = 0;
  textHeight = 32;
  fontSizeMultiplier = 2;
  fontType = 2;
  bufferBetweenText = visibleWidth;

  sprite->setColorDepth(1);
  sprite->setTextColor(TFT_WHITE);
  sprite->setTextSize(fontSizeMultiplier);
  sprite->setTextFont(fontType);
}

void ScrollableSprite::setText(String text) {
  this->text = text;
  spriteWidth = sprite->textWidth(text) + bufferBetweenText;
  
  sprite->deleteSprite(); //delete the old sprite to free up memory
  sprite->createSprite(spriteWidth, textHeight); 
  sprite->setScrollRect(0, 0, spriteWidth, textHeight);
  if(sprite->textWidth(text) <= visibleWidth) {
    int centerOffset = (visibleWidth - sprite->textWidth(text))/2;
    sprite->drawString(text, centerOffset, 0); 
  }
}

void ScrollableSprite::scrollText() {
  int scrollAmount = -1;
  sprite->pushSprite(xPosition, yPosition);
  
  if(sprite->textWidth(text) > visibleWidth) {
    sprite->scroll(scrollAmount);
    
    scrollCounter = scrollCounter - abs(scrollAmount);
    if (scrollCounter <= 0) {
      scrollCounter = spriteWidth;
    
      sprite->drawString(text, visibleWidth, 0); 
    }
  }
}