#ifndef Logger_h
#define Logger_h
#include "Arduino.h" 
class Logger {
public:
  Logger(void *outputFunction);
  void debug(String s);
  void log(String s);
private:
  void (*_outputFunction)(String s);
};
#endif