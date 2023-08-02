#ifndef BluetoothReceiver_h
#define BluetoothReceiver_h
#include "Arduino.h" 
#include "Logger.h" 
#include "MomentaryButton.h" 
#include "Receiver.h"
#include "BluetoothA2DPSink.h"

class BluetoothReceiver: public Receiver {
public:
  BluetoothReceiver();
  BluetoothReceiver(MomentaryButton &seekBack, MomentaryButton &playPause, MomentaryButton &seekForward, Logger &logger);
  void checkButtons();
  String getCurrentSong();
private:
  Logger _logger;
  MomentaryButton _seekBack;
  MomentaryButton _playPause;
  MomentaryButton _seekForward;
};

BluetoothA2DPSink& a2dp_sink(); 

#endif