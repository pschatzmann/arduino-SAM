#include "sam_arduino.h"

SAM sam(I2S_NUM_0);

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