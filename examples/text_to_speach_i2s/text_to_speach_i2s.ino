#include "sam_arduino.h"

SAM sam(I2S_NUM_0);

void setup(){
    Serial.begin(115700);
    sam.setVoice(SAM::Sam);
}


void loop(){
    const char* hallo ="hallo";
    Serial.println(hallo);
    sam.say(hallo);
    delay(1000);
}