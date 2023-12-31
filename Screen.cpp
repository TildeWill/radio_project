#include <JPEGDecoder.h>
#include <TFT_eSPI.h>

#include "Screen.h"
#include "ScrollableSprite.h"

// Return the minimum of two values a and b
#define minimum(a,b)     (((a) < (b)) ? (a) : (b))

Screen::Screen() {}

void Screen::wipeScreen() {
  this->fillScreen(TFT_BLACK);
  this->setSwapBytes(true);
}

void Screen::begin() {
  this->init();
  this->setRotation(0);  // portrait
  wipeScreen();

  titleSprite = new ScrollableSprite(this, this->width(), 0, 160, 2); 
  titleSprite->begin();
  artistSprite = new ScrollableSprite(this, this->width(), 0, 205, 1); 
  artistSprite->begin();
}


//####################################################################################################
// Draw a JPEG on the TFT pulled from a program memory array
//####################################################################################################
void Screen::drawJpeg(const uint8_t arrayname[], uint32_t array_size, int xpos, int ypos) {

  int x = xpos;
  int y = ypos;

  JpegDec.decodeArray(arrayname, array_size);
    
  renderJPEG(x, y);
}

//####################################################################################################
// Draw a JPEG on the TFT, images will be cropped on the right/bottom sides if they do not fit
//####################################################################################################
// This function assumes xpos,ypos is a valid screen coordinate. For convenience images that do not
// fit totally on the screen are cropped to the nearest MCU size and may leave right/bottom borders.
void Screen::renderJPEG(int xpos, int ypos) {

  // retrieve infomration about the image
  uint16_t *pImg;
  uint16_t mcu_w = JpegDec.MCUWidth;
  uint16_t mcu_h = JpegDec.MCUHeight;
  uint32_t max_x = JpegDec.width;
  uint32_t max_y = JpegDec.height;

  // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
  // Typically these MCUs are 16x16 pixel blocks
  // Determine the width and height of the right and bottom edge image blocks
  uint32_t min_w = minimum(mcu_w, max_x % mcu_w);
  uint32_t min_h = minimum(mcu_h, max_y % mcu_h);

  // save the current image block size
  uint32_t win_w = mcu_w;
  uint32_t win_h = mcu_h;

  // save the coordinate of the right and bottom edges to assist image cropping
  // to the screen size
  max_x += xpos;
  max_y += ypos;

  // read each MCU block until there are no more
  while (JpegDec.readSwappedBytes()) {
	  
    // save a pointer to the image block
    pImg = JpegDec.pImage ;

    // calculate where the image block should be drawn on the screen
    int mcu_x = JpegDec.MCUx * mcu_w + xpos;  // Calculate coordinates of top left corner of current MCU
    int mcu_y = JpegDec.MCUy * mcu_h + ypos;

    // check if the image block size needs to be changed for the right edge
    if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
    else win_w = min_w;

    // check if the image block size needs to be changed for the bottom edge
    if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
    else win_h = min_h;

    // copy pixels into a contiguous block
    if (win_w != mcu_w)
    {
      uint16_t *cImg;
      int p = 0;
      cImg = pImg + win_w;
      for (int h = 1; h < win_h; h++)
      {
        p += mcu_w;
        for (int w = 0; w < win_w; w++)
        {
          *cImg = *(pImg + w + p);
          cImg++;
        }
      }
    }

    // draw image MCU block only if it will fit on the screen
    if (( mcu_x + win_w ) <= this->width() && ( mcu_y + win_h ) <= this->height())
    {
      this->pushRect(mcu_x, mcu_y, win_w, win_h, pImg);
    }
    else if ( (mcu_y + win_h) >= this->height()) JpegDec.abort(); // Image has run off bottom of screen so abort decoding
  }
}

void Screen::debug(String message) {
  this->setCursor(0,200);
  this->setTextSize(2);
  this->println(message);
}

void Screen::setTitle(String title) {
  titleSprite->setText(title);
}

void Screen::scrollTitle() {
  titleSprite->scrollText();
}

void Screen::setArtist(String artist) {
  artistSprite->setText(artist);
}

void Screen::scrollArtist() {
  artistSprite->scrollText();
}