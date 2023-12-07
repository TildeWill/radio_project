#include <Arduino.h>
#include "BluetoothReceiver.h"
#include "Logger.h"
#include "BluetoothA2DPSink.h"

BluetoothA2DPSink& BluetoothReceiver::a2dp_sink() {           // add definition of the free function
    static BluetoothA2DPSink instance;
    return instance;
}

BluetoothReceiver::BluetoothReceiver() {}
BluetoothReceiver::BluetoothReceiver(MomentaryButton &seekBack, MomentaryButton &playPause, MomentaryButton &seekForward, Logger &logger, void(*avrc_metadata_callback)(uint8_t, const uint8_t*))
  : _seekBack(seekBack), _playPause(playPause), _seekForward(seekForward), _logger(logger), avrc_metadata_callback(avrc_metadata_callback) {
    a2dp_sink().set_avrc_metadata_callback(avrc_metadata_callback);
    
  a2dp_sink().start("Grandpa Johnson's Radio");
}

void BluetoothReceiver::checkButtons() {
  _seekBack.checkButton();
  _playPause.checkButton();
  _seekForward.checkButton();
}

void BluetoothReceiver::volumeUp() {
  _logger.log("Current volume:");
  _logger.log((String)a2dp_sink().get_volume());
  a2dp_sink().set_volume(a2dp_sink().get_volume()+5);
}
void BluetoothReceiver::volumeDown() {
  a2dp_sink().set_volume(a2dp_sink().get_volume()-5);
}




