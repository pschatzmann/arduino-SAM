#include "sam_arduino.h"

const i2s_config_t i2s_config = {
    .mode = (i2s_mode_t) (I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN),
    .sample_rate = 0, // dynamically determined
    .bits_per_sample = (i2s_bits_per_sample_t)16,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t) (I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = 0, // default interrupt priority
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false
};

SAM sam(new SAMOutputI2S(I2S_NUM_0, i2s_config));

void setup(){
    Serial.begin(115700);
    sam.setVoice(SAM::Sam);
}


void loop(){
    sam.say("Can you hear me now?");
    delay(500);
    sam.say("I can't hear you!");
    delay(2000);
}