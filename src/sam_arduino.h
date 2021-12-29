/**
 * @file sam_arduino.h
 * @author Phil Schatzmann
 * @brief Arduino API for SAM
 * @version 0.1
 * @date 2021-06-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sam_arduino_out.h"
#include "SamData.h"


/**
 * @brief Arduino API for SAM Text to Speach Engine
 * 
 */
class SAM {

    public:
        /// SAM Voices
        enum Voice {
            Elf,
            LittleRobot,
            StuffyGuy,
            LittleOldLaydy,
            ExtraTerrestrial,
            Sam,      
        };

        /// Constructor - for text output to Serial
        SAM(){
            SAM_LOG("SAM");
            setOutput(new SAMPrintStream(Serial));
            setVoice(Sam);
        }

        /// Constructor - for output to callback
        SAM(sam_callback cb){
            SAM_LOG("SAM callback");
            setOutput(new SAMOutputCallback(cb));
            setVoice(Sam);
        }

        /// Constructor - for output to a stream
        SAM(Print &stream, bool as_text=false){
            SAM_LOG("SAM Stream");
            if (as_text){
                setOutput(new SAMPrintStream(stream));
            } else {
                setOutput(new SAMOutputStream(stream));
            }
            setVoice(Sam);
        }

        /// Constructor - for output with a SAMOutputBase class
        SAM(SAMOutputBase &out){
            SAM_LOG("SAM SAMOutputBase");
            setOutput(&out);
            setVoice(Sam);
        }

        /// Constructor - for output with a SAMOutputBase class
        SAM(SAMOutputBase *out){
            SAM_LOG("SAM SAMOutputBase");
            setOutput(out);
            setVoice(Sam);
        }

#ifdef ESP32
        /// Constructor - for output to I2S
        SAM(i2s_port_t i2s_num){
            SAM_LOG("SAM i2s");
            setOutput(new SAMOutputI2S(i2s_num));
            setVoice(Sam);
        }
#endif

        /**
         * @brief Destroy the SAM object
         * 
         */
        ~SAM(){
            SAM_LOG("~SAM");
            end();
        }

        void setPitch(uint8_t pitch) {
			SetPitch(pitch);
        }

        void setSpeed(uint8_t speed) {
            SetSpeed(speed);
        }

        void setMouth(uint8_t mouth) {
			SetMouth(mouth);
        }

        void setThroat(uint8_t th) {
			SetThroat(th);
        }

        void setSingMode(bool sing){
            EnableSingmode(sing);
        }

        /**
         * @brief Set the Voice object
                DESCRIPTION          SPEED     PITCH     THROAT    MOUTH
                Elf                   72        64        110       160
                Little Robot          92        60        190       190
                Stuffy Guy            82        72        110       105
                Little Old Lady       82        32        145       145
                Extra-Terrestrial    100        64        150       200
                SAM                   72        64        128       128
         */
        void setVoice(Voice voice) {
            SAM_LOG("setVoice: %d", voice);
            switch(voice) {
                case Elf:
                    setSpeed(72);
                    setPitch(64);
                    setThroat(110);
                    setMouth(160);
                    break;
                case LittleRobot:
                    setSpeed(92);
                    setPitch(60);
                    setThroat(190);
                    setMouth(190);
                    break;
                case StuffyGuy:
                    setSpeed(82);
                    setPitch(72);
                    setThroat(110);
                    setMouth(105);
                    break;
                case LittleOldLaydy:
                    setSpeed(82);
                    setPitch(32);
                    setThroat(145);
                    setMouth(145);
                    break;
                case ExtraTerrestrial:
                    setSpeed(100);
                    setPitch(64);
                    setThroat(150);
                    setMouth(200);
                    break;
                case Sam:
                    setSpeed(72);
                    setPitch(64);
                    setThroat(128);
                    setMouth(128);
                    break;
            }
        };

        /// Process text input
        bool say(const char* text){
            SAM_LOG("say: %s",text);
            return textToSpeach(text, false);
        }

        /// Process text input
        bool sayPhone(const char* text){
            SAM_LOG("sayPhone: %s",text);
            return textToSpeach(text, true);
        }

        /// provides access to output information
        SAMOutputBase* getOutput() {
            return arduino_output;
        }

        /// Delete voice and cst_audio_streaming_info
        void end() {
            SAM_LOG("end");
            if(arduino_output!=nullptr && arduino_output->isOpen()){
                arduino_output->close();
            }
        }

        /// Defines the number of output channels  (default 1)
        void setOutputChannels(int channel_count){
            SAM_LOG("setOutputChannels: %d", channel_count);
            if (channel_count > 0){
                // fixed channels are not enforced
                this->channel_count = channel_count;
                arduino_output->setChannels(channel_count);
            } else {
                SAM_LOG("Channels is not supported for this output type");
            }
        }


        /// Provides the sample rate (44100)
        static int sampleRate() {
            return SAMOutputBase::sampleRate();
        }

        /// Provides the bits per sample
        int bitsPerSample() {
            return bits_per_sample;
        }

        /// Provides the number of channels
        int channels() {
            return channel_count;
        }

    protected:
        SAMOutputBase *arduino_output=nullptr;
        int bits_per_sample = 16;
        int channel_count = 1;
        uint8_t audio[2];
        int16_t *p_audio = (int16_t*)&audio;
        uint8_t audio_byte = 0;

        /// Used to feed the audio result back to this class 
        static void outputByteCallback(void *cbdata, unsigned char b) {
            SAM_LOG("outputByteCallback: %d", b);

            SAM *sam = static_cast<SAM*>(cbdata);
            sam->write(b);
        }

        void setOutput(SAMOutputBase *out){
            SAM_LOG("setOutput");
            arduino_output = out;    

            // synchronize channels definition with arduino_output: I2S must be 2 therefore we try to get it from arduino_output first
            if (arduino_output->channels()!=-1){
                this->channel_count = arduino_output->channels();
            } else {
                arduino_output->setChannels(channel_count);
            }
            SAM_LOG("-> channel_count: %d",this->channel_count);
            SAM_LOG("-> bits_per_sample: %d",this->bits_per_sample);
        }

        /// Writes the data to the output. The data is provided on 1 channel as unsinged byte of int16 values
        void write(uint8_t in) {            
            SAM_LOG("SAM::write bps:%d / channels:%d",bits_per_sample, channel_count);
            audio[audio_byte++] = in;

            if (audio_byte==2){
                audio_byte = 0;
                int16_t value = *p_audio;

                // provide multiple channels if necessary
                int16_t sample[channel_count];
                for (int j=0;j<channel_count;j++){
                    sample[j] = value;
                }
                SAM_LOG("writing to %s", arduino_output->name());
                arduino_output->write((byte*)sample, channel_count*2);
            }
        }

        bool textToSpeach(const char *str, bool is_phonetic) {
            SAM_LOG("textToSpeach: %s",str);
     
            if (!str || strlen(str)>254) return false; // Only can speak up to 1 page worth of data...
            samdata = new SamData();
            if (samdata == nullptr){
                // allocation failed!
                return false;
            }            
            arduino_output->open();

            // Input massaging
            char input[256];
            for (int i=0; str[i]; i++)
                input[i] = toupper((int)str[i]);
            input[strlen(str)] = 0;
            SAM_LOG("input copied");

            // To phonemes
            if (is_phonetic) {
                strncat(input, "\x9b", 255);
            } else {
                SAM_LOG("TextToPhonemes");
                strncat(input, "[", 255);
                if (!TextToPhonemes(input)) return false; // ERROR
            }
            // Say it!
            SAM_LOG("SetInput: %s", input);
            SetInput(input);

            SAM_LOG("SAMMain");
            SAMMain(outputByteCallback, (void*)this);
            SAM_LOG("SAMMain - done");

            // close the processing
            SAM_LOG("SAM done!");
            arduino_output->close();

            // Release SamData
            delete samdata;

            return true;
        }
};

void printLog(char* msg){
    Serial.println(msg);
}

/**
 * @brief string and pitch - this can be used to build a song
 * 
 */
struct PitchedStr {
    int pitch;
    char* str;
};