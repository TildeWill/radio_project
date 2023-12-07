#ifndef Logger_h
#define Logger_h
#include "Arduino.h" 
class Logger {
public:
  Logger();
  Logger(void (*outputFunction)(const String &s));
  
  void debug(const String &s);
  void log(const String &s);
  void log(const int &i);
private:
  void (*_outputFunction)(const String &s);
};
#endif