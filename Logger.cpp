#include <Arduino.h>
#include "Logger.h"

Logger::Logger() { }

Logger::Logger(void (*outputFunction)(const String &s)) {
  _outputFunction = outputFunction;
}

void Logger::debug(const String &s){
  _outputFunction("DEBUG: " + s);
}

void Logger::log(const String &s){
  _outputFunction(s);
}

void Logger::log(const int &i){
  _outputFunction(String(i));
}