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
    
    // i2s_pin_config_t myPinConfig = {
    //     .bck_io_num = 26, //BCLK
    //     .ws_io_num = 27,  
    //     .data_out_num = 25, //DIN
    //     .data_in_num = I2S_PIN_NO_CHANGE
    // };
    // a2dp_sink().set_pin_config(myPinConfig);

    const i2s_config_t i2s_config = {
      .mode = (i2s_mode_t) (I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN),
      .sample_rate = 44100, // corrected by info from bluetooth
      .bits_per_sample = (i2s_bits_per_sample_t) 16, /* the DAC module will only take the 8bits from MSB */
      .channel_format =  I2S_CHANNEL_FMT_RIGHT_LEFT,
      .communication_format = (i2s_comm_format_t)I2S_COMM_FORMAT_STAND_MSB,
      .intr_alloc_flags = 0, // default interrupt priority
      .dma_buf_count = 8,
      .dma_buf_len = 64,
      .use_apll = false
  };

  a2dp_sink().set_i2s_config(i2s_config); 
  a2dp_sink().start("Grandpa Johnson's Radio");
}

void BluetoothReceiver::checkButtons() {
  _seekBack.checkButton();
  _playPause.checkButton();
  _seekForward.checkButton();
}




