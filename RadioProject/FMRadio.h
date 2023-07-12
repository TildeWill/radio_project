#ifndef FMRadio_h
#define FMRadio_h
#include "Arduino.h" 
#include "Logger.h" 
#include "MomentaryButton.h" 

class FMRadio {
public:
  FMRadio();
  FMRadio(MomentaryButton &seekBack, MomentaryButton &playPause, MomentaryButton &seekForward, Logger &logger);
  void checkButtons();
private:
  Logger _logger;
  MomentaryButton _seekBack;
  MomentaryButton _playPause;
  MomentaryButton _seekForward;
};
#endif