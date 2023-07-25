#include <Arduino.h>
#include "Logger.h"

Logger::Logger() { }

Logger::Logger(void (*outputFunction)(String s)) {
  _outputFunction = outputFunction;
}

void Logger::debug(String s){
  _outputFunction("DEBUG: " + s);
}

void Logger::log(String s){
  _outputFunction(s);
}