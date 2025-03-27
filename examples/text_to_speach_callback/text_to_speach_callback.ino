#include "sam_arduino.h"

void callback(size_t len, void *data){
    int16_t *data16 = (int16_t *)data;
    for (size_t j=0;j<len;j++){
        Serial.println(data16[j]);
    }
}

SAM sam(callback);

void setup(){
    Serial.begin(115200);
    sam.setVoice(SAM::Sam);
    sam.setOutputBitsPerSample(16);
    sam.setOutputChannels(1);
}


void loop(){
    const char* hallo ="hallo";
    Serial.println(hallo);
    sam.say(hallo);
    
    delay(1000);
}