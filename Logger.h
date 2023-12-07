#ifndef Logger_h
#define Logger_h
#include "Arduino.h" 
class Logger {
public:
  Logger();
  Logger(void (*outputFunction)(String s));
  
  void debug(String s);
  void log(String s);
private:
  void (*_outputFunction)(String s);
};
#endif