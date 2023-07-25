#ifndef MomentaryButton_h
#define MomentaryButton_h
#include "Arduino.h" 
#include "Logger.h" 
class MomentaryButton {
public:
  MomentaryButton();
  MomentaryButton(int pin, void (*pressedCallback)(void), Logger &logger);
  
  void checkButton();
private:
  int _pin;
  byte _lastButtonState;
  unsigned long _debounceDuration; // millis
  unsigned long _lastTimeButtonStateChanged;
  void (*_pressedCallback)(void);
  Logger _logger;
};
#endif