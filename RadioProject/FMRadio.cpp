#include <Arduino.h>
#include "FMRadio.h"
#include "Logger.h"

FMRadio::FMRadio() {}
FMRadio::FMRadio(MomentaryButton &seekBack, MomentaryButton &playPause, MomentaryButton &seekForward, Logger &logger)
  : _seekBack(seekBack), _playPause(playPause), _seekForward(seekForward), _logger(logger) {
}

void FMRadio::checkButtons() {
  _seekBack.checkButton();
  _playPause.checkButton();
  _seekForward.checkButton();
}

String FMRadio::getCurrentSong() {
  return "Bad Blood - Taylor Swift";
}