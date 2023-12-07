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
  BluetoothReceiver(MomentaryButton &seekBack, MomentaryButton &playPause, MomentaryButton &seekForward, Print *logger, void(*avrc_metadata_callback)(uint8_t, const uint8_t*));
  void checkButtons();
  void volumeUp();
  void volumeDown();
private:
  Print *_logger;
  MomentaryButton _seekBack;
  MomentaryButton _playPause;
  MomentaryButton _seekForward;
  BluetoothA2DPSink& a2dp_sink(); 
  void(*avrc_metadata_callback)(uint8_t, const uint8_t*);
};



#endif