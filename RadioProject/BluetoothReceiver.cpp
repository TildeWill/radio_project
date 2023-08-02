#include <Arduino.h>
#include "BluetoothReceiver.h"
#include "Logger.h"
#include "BluetoothA2DPSink.h"

BluetoothA2DPSink& a2dp_sink() {           // add definition of the free function
    static BluetoothA2DPSink instance;
    return instance;
}

BluetoothReceiver::BluetoothReceiver() {}
BluetoothReceiver::BluetoothReceiver(MomentaryButton &seekBack, MomentaryButton &playPause, MomentaryButton &seekForward, Logger &logger)
  : _seekBack(seekBack), _playPause(playPause), _seekForward(seekForward), _logger(logger) {
    a2dp_sink().start("JohnsonRadio2");
}

void BluetoothReceiver::checkButtons() {
  _seekBack.checkButton();
  _playPause.checkButton();
  _seekForward.checkButton();
}

String BluetoothReceiver::getCurrentSong() {
  return "Bad Blood - Taylor Swift";
}




