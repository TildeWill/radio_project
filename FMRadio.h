#ifndef FMRadio_h
#define FMRadio_h
#include "Arduino.h" 
#include "Logger.h" 
#include "MomentaryButton.h" 
#include "Receiver.h"

class FMRadio: public Receiver {
public:
  FMRadio();
  FMRadio(MomentaryButton &seekBack, MomentaryButton &playPause, MomentaryButton &seekForward, Print *logger);
  void checkButtons();
  void volumeUp(int amount);
  void volumeDown(int amount);
private:
  Print *_logger;
  MomentaryButton _seekBack;
  MomentaryButton _playPause;
  MomentaryButton _seekForward;
};
#endif