#include <TFT_eSPI.h>

#include "ScrollableSprite.h"

ScrollableSprite::ScrollableSprite(TFT_eSPI* tft, int visibleWidth, int xPosition, int yPosition, int fontSizeMultiplier) : 
  TFT_eSprite(tft), visibleWidth(visibleWidth), xPosition(xPosition), yPosition(yPosition), fontSizeMultiplier(fontSizeMultiplier) {}

void ScrollableSprite::begin() {
  scrollCounter = 0;
  textHeight = 16 * fontSizeMultiplier;
  fontType = 2;
  bufferBetweenText = visibleWidth;

  this->setColorDepth(1);
  this->setTextColor(TFT_WHITE);
  this->setTextSize(fontSizeMultiplier);
  this->setTextFont(fontType);
}

void ScrollableSprite::setText(String text) {
  this->text = text;
  spriteWidth = this->textWidth(text) + bufferBetweenText;
  
  this->deleteSprite(); //delete the old sprite to free up memory
  this->createSprite(spriteWidth, textHeight); 
  this->setScrollRect(0, 0, spriteWidth, textHeight);
  if(this->textWidth(text) <= visibleWidth) {
    int centerOffset = (visibleWidth - this->textWidth(text))/2;
    this->drawString(text, centerOffset, 0); 
  }
}

void ScrollableSprite::scrollText() {
  int scrollAmount = -1;
  this->pushSprite(xPosition, yPosition);
  
  if(this->textWidth(text) > visibleWidth) {
    this->scroll(scrollAmount);
    
    scrollCounter = scrollCounter - abs(scrollAmount);
    if (scrollCounter <= 0) {
      scrollCounter = spriteWidth;
    
      this->drawString(text, visibleWidth, 0); 
    }
  }
}