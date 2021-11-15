#include "sam_arduino.h"

// as_text=true
SAM sam(Serial,true);

void setup(){
    Serial.begin(115700);
    sam.setVoice(SAM::Sam);
    sam.setOutputBitsPerSample(8);
    sam.setOutputChannels(1);
}


void loop(){
    const char* hallo ="hallo my name is SAM";
    Serial.println(hallo);
    sam.say(hallo);
    
    delay(1000);
}
