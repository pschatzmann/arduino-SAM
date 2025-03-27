#include "sam_arduino.h"

SAM sam(I2S_NUM_0);
const char *hallo = "sam hello my name is SAM. I will sing the national anthem of the united states of america the star spangled banner"
const PitchedStr song[] = {
    {64, "ohohoh"},
    {76, "ohohoh"},
    {96 , "sehehehehehehehehehey"},
    {76 , "kaeaeaeaeaeaeaeaeaen"},
    {64 , "yuxuxuxuxuxuxw"},
    {48 , "siyiyiyiyiyiyiyiyiyiyiyiyiyiyiyiyiyiy"},
    {38 , "baaaaay"},
    {42 , "dhaaaxaxaxax"},
    {48 , "daoaoaoaoaoaoaonz"},
    {76 , "ererererererer"},
    {68 , "liyiyiyiyiyiyiyiyiy"},
    {64 , "laaaaaaaaaaaaaaaaaaaaaaaaayt"},
    {64 , "whahahaht"},
    {64 , "sohohuw"},
    {38 , "praaaaaaaaaaaaaaaauwd"},
    {42 , "liyiyiy"},
    {48 , "wiyiyiyiyiyiyiyiyiy"},
    {51 , "/heheheheheheheheheheheheheheheheheheyld"},
    {56 , "aeaeaeaet"},
    {51 , "dhaaaxaxaxax"},
    {48 , "twaaaaaaaaaaaaaaiy"},
    {48 , "laaaaaaaaaaaaiyts"},
    {64 , "laeaeaeaeaeaeaeaeaest"},
    {76 , "gliyiyiyiyiyiyiyiyiym"},
    {96 , "mihihihihihihihihihihnx"},
    {64 , "/huxuxuxuxuxuxuxuxuxuxwz"},
    {76 , "braoaoaod"},
    {96 , "straaaaaaaaaaaaiyps"},
    {76 , "aeaeaeaeaeaeaeaeaeaend"},
    {64 , "braaaaaaaaaaaaaaiyt"},
    {48 , "staaaaaaaaaaaaaaaaaaaaaaaaaarz"},
    {38 , "thruxuxw"},
    {42 , "dhaaaxaxaxax"},
    {48 , "pehehehehehehehehehehr"},
    {76 , "rixixixixixixixixixixixixl"},
    {68 , "lahahahahahahahahahs"},
    {64 , "faaaaaaaaaaaaaaaaaaaaaaaaaaiyt"},
    {64 , "ohohohr"},
    {64 , "dhaaaxaxaxax"},
    {38 , "raeaeaeaeaeaeaeaeaeaeaeaem"},
    {42 , "paaaarts"},
    {48 , "wiyiyiyiyiyiyiyiyiy"},
    {51 , "waaaaaaaaaaaaaaaaaaaaaaaaaachd"},
    {56 , "werer"},
    {51 , "sohohw"},
    {48 , "gaeaeaeaeaeaeaeaeaeael"},
    {48 , "lixixixixixixixixixixixixixnt"},
    {64 , "liyiyiyiyiyiyiyiyiy"},
    {76 , "striyiyiyiyiyiyiyiyiym"},
    {96 , "mihihihihihihihihihnx"},
    {38 , "aeaeaeaeaend"},
    {38 , "dhaaaxaxaxax"},
    {38 , "raaaaaaaaaaaak"},
    {36 , "kixixixixixixixixixixixts"},
    {32 , "rehehehehehehehehehd"},
    {32 , "gleheheheheheheheheheheheheheheherer"},
    {36 , "dhaaaxaxaxax"},
    {38 , "baaaamz"},
    {42 , "bererererererst"},
    {38 , "tihihihihihihihihihnx"},
    {36 , "ihihihihihihihihihihn"},
    {36 , "eheheheheheheheheheheheheheheheheheyr"},
    {36 , "geheheheyv"},
    {38 , "pruxuxuxuxuxuxuxuxuxuxuxuxwf"},
    {42 , "thruxuxw"},
    {48 , "dhaaaxaxax"},
    {51 , "naaaaaaaaaaaaaaaaaaaaaaayiyt"},
    {56 , "dhaeaeaeaet"},
    {51 , "aaaaaauwr"},
    {48 , "flaeaeaeaeaeaeaeaeaeg"},
    {76 , "wahahahahahahahahahz"},
    {68 , "stihihihihihihihihihl"},
    {64 , "dhehehehehehehehehehehehehehehehehehehehr"},
    {64 , "ohohohohohohow"},
    {48 , "sehehehehehehehehehey"},
    {48 , "dahahahahahahahahahz"},
    {48 , "dhaeaeae"},
    {51 , "aeaeaet"},
    {56 , "staaaaaaaaaaaar"},
    {56 , "spehehehehehehehehehiynx"},
    {56 , "gaxaxaxaxaxaxaxaxaxaxaxaxld"},
    {42 , "baeaeaeaeaeaeaeaeaen"},
    {36 , "nerer"},
    {38 , "ererer"},
    {42 , "yehehehv
    {48 , "ehehehehtv
    {48 , "weheheheheheheheheheheh"},
    {51 , "ehehehehehehehiyiyiyv"},
    {64 , "ohohohr"},
    {64 , "dhaaaxaxaxax"},
    {48 , "laeaeaeaeaeaeaeaeaeaeaeae"},
    {42 , "aeaeaend"},
    {38 , "ahahahv"},
    {36 , "dhaaaxaxaxax"},
    {32 , "friyiyiyiyiyiyiyiyiyiyiyiyiyiyiyiyiyiy"},
    {48 , "aeaeaend"},
    {42 , "dhaaaxaxaxax"},
    {38 , "/hohohohohohohohohowm"},
    {36 , "ahahahahv"},
    {42 , "dhaaaxaxaxaxaxaxaxaxaxaxaxaxax"},
    {48 , "brehehehehehehehehehehiyiyiyv"}};


void setup(){
    Serial.begin(115200);
    sam.setSingMode(true);
}

void loop(){
    Serial.println(hallo);
    sam.say(hallo);
    for (auto rec in song){
        sam.setPitch(rec.pitch)
        sam.sayPhone(rec.str);
    }
    delay(5000);
}