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
#include "reciter.h"
#include "sam.h"
#include "sam_config.h"

#if defined(ESP32) && LEGACY_ESP_I2S
#include "driver/i2s.h"
#include "freertos/queue.h"
#endif

// User Callback
typedef void (*sam_callback)(size_t size, int16_t *values);

// Application Callback
static void OutputByteCallback(void *cbdata, unsigned char b);
static uint32_t SAM_sample_rate = 22050;
/**
 * @brief Base Output Class with common functionality
 *
 */
class SAMOutputBase {
 public:
  virtual ~SAMOutputBase() {}

  virtual void open() {
    SAM_LOG("SAMOutputBase::open");
    is_open = true;
  };

  virtual int close() {
    is_open = false;
    return 0;
  }

  virtual int drain() { return 0; }

  virtual int channels() { return channel_count; }

  virtual void setChannels(int channels) { channel_count = channels; }

  virtual int bitsPerSample() { return 16; }

  virtual bool isOpen() { return is_open; }

  static uint32_t sampleRate() {
    return SAM_sample_rate;  // 44100;
  }

  static void setSampleRate(uint32_t rate) {
    SAM_sample_rate = rate;  // 44100;
  }

  virtual const char *name() = 0;

  virtual bool write(byte *buff, int bytes_count) = 0;

 protected:
  bool is_open = false;
  int channel_count = -1;
  int bits_per_sample = -1;
};

/**
 * @brief Output via Callback method
 *
 */
class SAMOutputCallback : public SAMOutputBase {
 public:
  SAMOutputCallback(sam_callback cb) { callback = cb; }

  virtual bool write(byte *buffer, int bytes_count) {
    SAM_LOG("SAMOutputCallback::write: %d", bytes_count);
    int samples = bytes_count / sizeof(int16_t);
    callback(samples, (int16_t *)buffer);
    return true;
  }

  const char *name() { return "SAMOutputCallback"; }

 protected:
  sam_callback callback;
};

#if defined(ESP32) && LEGACY_ESP_I2S
#if __has_include("esp_arduino_version.h")
#include "esp_arduino_version.h"
#endif

#if !defined(ESP_IDF_VERSION_MAJOR)
#define ESP_IDF_VERSION_MAJOR 2
#endif

#if ESP_IDF_VERSION_MAJOR < 4
#define I2S_COMM_FORMAT_STAND_I2S \
  (I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB)
#endif

/**
 * @brief Output to I2S for ESP32: This class is obsolete and has been
 * deactivated in the sam_config.h since the related API is not longer supported
 * by Espressif. Use the I2S functionality provided by your core or the
 * AudioTools library instread.
 *
 */
class SAMOutputI2S : public SAMOutputBase {
 public:
  SAMOutputI2S(i2s_port_t i2s_num = I2S_NUM_0) {
    this->i2s_num = i2s_num;
    setupDefaultConfig();
    setupDefaultPins();
  }

  SAMOutputI2S(i2s_port_t i2s_num, i2s_config_t cfg) {
    this->i2s_num = i2s_num;
    this->i2s_config = cfg;
    setupDefaultPins();
  }

  SAMOutputI2S(i2s_port_t i2s_num, i2s_config_t cfg, i2s_pin_config_t pins) {
    this->i2s_num = i2s_num;
    this->i2s_config = cfg;
    this->pin_config = pins;
  }

  ~SAMOutputI2S() {
    if (isOpen()) {
      close();
    }
  }

  const char *name() { return "SAMOutputI2S"; }

  int channels() { return 2; }

  virtual void open() {
    // update sample sample_rate
    i2s_config.sample_rate = SAMOutputBase::sampleRate();
    SAM_LOG("setting sample rate for I2S: %d", i2s_config.sample_rate);
    // install driver
    if (i2s_driver_install(i2s_num, &i2s_config, 0, NULL) != ESP_OK) {
      ESP_LOGE(TAG, "Failed to install i2s");
    }
    if (i2s_config.mode & I2S_MODE_DAC_BUILT_IN) {
      // for internal DAC, this will enable both of the internal channels
      SAM_LOG("i2s_set_pin: %s", "internal DAC");
      if (i2s_set_pin(i2s_num, NULL) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set i2s pins");
      }
    } else {
      // define pins for external DAC
      SAM_LOG("i2s_set_pin: %s", "external DAC");
      if (i2s_set_pin(i2s_num, &pin_config) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set i2s pins");
      }
    }
    SAMOutputBase::open();
  };

  virtual int close() {
    if (i2s_driver_uninstall(i2s_num) != ESP_OK) {
      ESP_LOGE(TAG, "Failed to uninstall i2s");
    }

    return SAMOutputBase::close();
  }

  virtual int drain() {
    i2s_zero_dma_buffer(i2s_num);
    return 0;
  }

  virtual bool write(byte *buffer, int bytes_count) {
    SAM_LOG("SAMOutputI2S::write: %d", bytes_count);
    size_t i2s_bytes_write;

    if (this->i2s_config.mode & I2S_MODE_DAC_BUILT_IN) {
      for (int i = 0; i < bytes_count; i++) {
        buffer[i] = buffer[i] + 0x8000;
      }
    }

    if (i2s_write(i2s_num, buffer, bytes_count,
                  &i2s_bytes_write, portMAX_DELAY) != ESP_OK) {
      ESP_LOGE(TAG, "i2s_write failed!");
      return false;
    }
    return true;
    ;
  }

  void setChannels(int ch) {
    if (ch != 2) SAM_LOG("Channels is not supported for this output type");
  }

  void setBitsPerSample(int bps) {
    if (bps != 16) SAM_LOG("Channels is not supported for this output type");
  }

 protected:
  i2s_port_t i2s_num;
  i2s_config_t i2s_config;
  i2s_pin_config_t pin_config;
  const char *TAG = "SAMOutputI2S";

  void setupDefaultConfig() {
    const i2s_config_t i2s_config_default = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = this->sampleRate(),
        .bits_per_sample = (i2s_bits_per_sample_t)16,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = (i2s_comm_format_t)I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,  // lowest interrupt priority
        .dma_buf_count = 10,
        .dma_buf_len = 64,
        .use_apll = false,
        .tx_desc_auto_clear =
            true  // avoiding noise in case of data unavailability
    };
    this->i2s_config = i2s_config_default;
  }

  void setupDefaultPins() {
    static const i2s_pin_config_t pin_config_default = {
        .bck_io_num = 26,
        .ws_io_num = 25,
        .data_out_num = 22,
        .data_in_num = I2S_PIN_NO_CHANGE};
    this->pin_config = pin_config_default;
  }
};
#endif

/**
 * @brief Output to Arduino Stream
 *
 */
class SAMOutputStream : public SAMOutputBase {
 public:
  SAMOutputStream(Print &out) { this->out_ptr = &out; }
  const char *name() { return "SAMOutputStream"; }

  virtual int drain() { return 0; }

  virtual bool write(byte *buffer, int bytes_count) {
    SAM_LOG("SAMOutputStream::write: %d", bytes_count);
    size_t len = bytes_count;

    size_t len_written = out_ptr->write((const uint8_t *)buffer, len);
    if (len != len_written) {
      SAM_LOG("Error - Could not write all data: %d of %d", len_written, len);
      return false;
    }
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
class SAMPrintStream : public SAMOutputStream {
 public:
  SAMPrintStream(Print &out) : SAMOutputStream(out) {}

  const char *name() { return "SAMPrintStream"; }

  virtual bool write(byte *buffer, int bytes_count) {
    // copy from 1 to 2 channels
    int16_t *buffer16 = (int16_t *)buffer;
    for (int j = 0; j < bytes_count / 2; j++) {
      out_ptr->print(buffer16[j]);
      if (j < channels() - 1) {
        out_ptr->print(",");
      }
      if (j == channels() - 1) {
        out_ptr->println();
      }
    }

    return true;
  }
};
