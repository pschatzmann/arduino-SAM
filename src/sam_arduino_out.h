/**
 * @file sam_out_arduino.h
 * @author Phil Schatzmann
 * @brief Arduino C++ Output Alternatives. 
 * @version 0.1
 * @date 2021-06-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Arduino.h"
#include "sam_config.h"
#include "sam.h"
#include "reciter.h"

#ifdef ESP32
#include "driver/i2s.h"
#include "freertos/queue.h"
#endif

// User Callback
typedef void (*sam_callback)(size_t size, void *values);

// Application Callback
static void OutputByteCallback(void *cbdata, unsigned char b);

/**
 * @brief Base Output Class with common functionality
 * 
 */
class SAMOutputBase {
    public:
        virtual ~SAMOutputBase(){
        }

        virtual void open() {
            SAM_LOG("SAMOutputBase::open");
            is_open = true;
        };

        virtual int close() {
            is_open = false;
            return 0;
        }

        virtual int drain(){
            return 0;
        }

        virtual int flush(){
            return 0;
        }

        virtual int channels() {
            return channel_count;
        }

        virtual int bitsPerSample() {
            return bits_per_sample;
        }

        virtual bool isOpen() {
            return is_open;
        }

        static int sampleRate() {
            return 22050;
        }

        void setBitsPerSample(int bps) {
            bits_per_sample = bps;
        }

        virtual const char* name() = 0;

        virtual bool write(byte *buff,int bytes_count) = 0;

    protected:
        bool is_open = false;
        int channel_count = -1;
        int bits_per_sample = -1;
};

/**
 * @brief Output via Callback method
 * 
 */
class SAMOutputCallback : public  SAMOutputBase {
    public:
        SAMOutputCallback(sam_callback cb){
            callback = cb;
        }

        virtual bool write(byte *buffer,int bytes_count) {
            SAM_LOG("SAMOutputCallback::write: %d",  bytes_count);
            int size = bytes_count;
            callback(size, (int8_t*) buffer);
            return true;
        }

        const char *name() {
            return "SAMOutputCallback";
        }

    protected:
        sam_callback callback;
};

#ifdef ESP32
/**
 * @brief Output to I2S for ESP32
 * 
 */
class SAMOutputI2S : public  SAMOutputBase {
    public:
        SAMOutputI2S(i2s_port_t i2s_num=I2S_NUM_0){
            this->i2s_num = i2s_num;
            setupDefaultConfig();
            setupDefaultPins();
        }

        SAMOutputI2S(i2s_port_t i2s_num, i2s_config_t cfg){
            this->i2s_num = i2s_num;
            this->i2s_config = cfg;
            setupDefaultPins();
        }

        SAMOutputI2S(i2s_port_t i2s_num, i2s_config_t cfg, i2s_pin_config_t pins ){
            this->i2s_num = i2s_num;
            this->i2s_config = cfg;
            this->pin_config = pins;
        }

        ~SAMOutputI2S(){
            if (isOpen()){
                close();
            }
        }

        const char *name() {
            return "SAMOutputI2S";
        }

        int channels() {
            return 2;
        }

        int bitsPerSample() {
            return 16;
        }

        virtual void open() {
            // update sample sample_rate
            i2s_config.sample_rate = SAMOutputBase::sampleRate();
            SAM_LOG("setting sample rate for I2S: %d", i2s_config.sample_rate);
            // install driver
            if (i2s_driver_install(i2s_num, &i2s_config, 0, NULL)!=ESP_OK){
                ESP_LOGE(TAG,"Failed to install i2s");
            }
            if (i2s_config.mode & I2S_MODE_DAC_BUILT_IN) {
                //for internal DAC, this will enable both of the internal channels
                SAM_LOG("i2s_set_pin: %s","internal DAC");
                if (i2s_set_pin(i2s_num, NULL)!=ESP_OK){
                    ESP_LOGE(TAG,"Failed to set i2s pins");
                }
            } else {
                // define pins for external DAC
                SAM_LOG("i2s_set_pin: %s","external DAC");
                if (i2s_set_pin(i2s_num, &pin_config)!=ESP_OK){
                    ESP_LOGE(TAG,"Failed to set i2s pins");
                }
            }
            SAMOutputBase::open();
        };

        virtual int close() {
            if (i2s_driver_uninstall(i2s_num) != ESP_OK){
                ESP_LOGE(TAG,"Failed to uninstall i2s");
            }

            return SAMOutputBase::close();
        }

        virtual int drain(){
            i2s_zero_dma_buffer(i2s_num);
            return 0;
        }

        virtual bool write(byte *buffer,int bytes_count) {
            SAM_LOG("SAMOutputI2S::write: %d",  bytes_count);
            size_t i2s_bytes_write;

            if (this->i2s_config.mode & I2S_MODE_DAC_BUILT_IN) {        
                for (int i=0; i < bytes_count ; i++) {
                    buffer[i]= buffer[i] + 0x8000;
                }
            }

            if (i2s_write(i2s_num, buffer, bytes_count*sizeof(int16_t), &i2s_bytes_write, portMAX_DELAY)!=ESP_OK){
                ESP_LOGE(TAG,"i2s_write failed!");
                return false;
            }
            return true;;
        }

    protected:
        i2s_port_t i2s_num;  
        i2s_config_t i2s_config;
        i2s_pin_config_t pin_config;
        const char *TAG = "SAMOutputI2S";

        void setupDefaultConfig() {
            const i2s_config_t i2s_config_default = {
                .mode = (i2s_mode_t) (I2S_MODE_MASTER | I2S_MODE_TX),
                .sample_rate = this->sampleRate(),
                .bits_per_sample = (i2s_bits_per_sample_t)16,
                .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
                .communication_format = (i2s_comm_format_t) (I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
                .intr_alloc_flags = 0, // default interrupt priority
                .dma_buf_count = 8,
                .dma_buf_len = 64,
                .use_apll = false
            };
            this->i2s_config = i2s_config_default;
        }

        void setupDefaultPins() {
            static const i2s_pin_config_t pin_config_default = {
                .bck_io_num = 26,
                .ws_io_num = 25,
                .data_out_num = 22,
                .data_in_num = I2S_PIN_NO_CHANGE
            };
            this->pin_config = pin_config_default;
        }

};
#endif

/**
 * @brief Output to Arduino Stream
 * 
 */
class SAMOutputStream : public  SAMOutputBase {
    public:
        SAMOutputStream(Print &out){
            this->out_ptr = &out;
        }
        const char *name() {
            return "SAMOutputStream";
        }

        virtual int drain(){
            // while(out_ptr->available()>0){
            //     out_ptr->read();
            // }
            return 0;
        }

        virtual int flush(){
            //out_ptr->flush();
            return 0;
        };


        virtual bool write(byte *buffer, int bytes_count) {
            SAM_LOG("SAMOutputStream::write: %d",  bytes_count);
            size_t len = bytes_count*sizeof(int16_t);

            size_t len_written = out_ptr->write((const uint8_t *) buffer, len);
            if (len!=len_written){
                SAM_LOG("Error - Could not write all data: %d of %d", len_written, len);
                return false;
            }
            //out_ptr->flush();
            return true;
        }

    protected:
        Print *out_ptr;   
        int output_channels;    
};

/**
 * @brief Write readable string to Arduino Stream
 * 
 */
class SAMPrintStream : public  SAMOutputStream {
    public:
        SAMPrintStream(Print &out) : SAMOutputStream(out) {
        }

        const char *name() {
            return "SAMPrintStream";
        }

        virtual bool write(byte *buffer,int bytes_count) {
            switch(bitsPerSample()){
                case 8:
                    // copy from 1 to 2 channels
                    for (int j=0;j<bytes_count;j++){
                        out_ptr->println(buffer[j]);
                    }
                    break;

                case 16:
                    // copy from 1 to 2 channels
                    int16_t *buffer16 = (int16_t *) buffer;
                    for (int j=0;j<bytes_count/2;j++){
                        out_ptr->println(buffer16[j]);
                    }
                    break;
                
            }

            return true;
        }

};

