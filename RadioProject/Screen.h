#ifndef Screen_h
#define Screen_h
#include "Arduino.h" 
#include <SPI.h>
#include <TFT_eSPI.h>

class Screen {
public:
  Screen();
  void begin();
  void drawJpeg(const uint8_t arrayname[], uint32_t array_size, int xpos, int ypos);
private:
  TFT_eSPI& tft(); 
  void renderJPEG(int xpos, int ypos);
};



#endif