#include <Arduino.h>
#include "MomentaryButton.h"
#include "Logger.h" 

MomentaryButton::MomentaryButton() {}
MomentaryButton::MomentaryButton(int pin, void (*pressedCallback)(void), Print *logger):
  _logger(logger)
 {
	pinMode(pin, INPUT);
	_pin = pin;
  _pressedCallback = pressedCallback;
  _lastButtonState = LOW;
  _debounceDuration = 50;
  _lastTimeButtonStateChanged = 0;
}
void MomentaryButton::checkButton() {
  if (millis() - _lastTimeButtonStateChanged > _debounceDuration) {
      byte buttonState = digitalRead(_pin);
      if (buttonState != _lastButtonState) {
      _lastTimeButtonStateChanged = millis();
      _lastButtonState = buttonState;
      if (buttonState == HIGH) {
        // do an action, for example print on Serial
        _logger->println("Button pressed");
        _pressedCallback();
      }
    }
  }
}