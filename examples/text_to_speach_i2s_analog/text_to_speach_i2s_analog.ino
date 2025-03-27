#include "AudioTools.h" // https://github.com/pschatzmann/arduino-audio-tools
#include "sam_arduino.h"

AnalogAudioStream out;
SAM sam(out);

void setup(){
    Serial.begin(115200);

    sam.setVoice(SAM::Sam);

    auto cfg = out.defaultConfig();
    cfg.sample_rate = 22050;
    cfg.channels = 1;
    cfg.bits_per_sample = 16;
    out.begin(cfg);
}


void loop(){
    sam.say("Can you hear me now?");
    delay(500);
    sam.say("I can't hear you!");
    delay(2000);
}