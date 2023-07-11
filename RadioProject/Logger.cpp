#include <Arduino.h>
#include "Logger.h"

Logger::Logger(void *outputFunction) {
  _outputFunction = outputFunction;
}

void Logger::debug(String s){
  _outputFunction(s);
}