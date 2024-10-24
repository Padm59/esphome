#include "attiny85_i2c.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"


namespace esphome {
namespace attiny85_i2c {

static const char *const TAG = "attiny85_i2c";


void ATtiny85I2C::setup() {
  ESP_LOGV(TAG, "Entering setup...");
  update_frequency(this->frequency_);

}

void ATtiny85I2C::dump_config() {
  
    if (this->is_failed()) {
        ESP_LOGE(TAG, "Setting up ATtiny85PWM failed!");
    } else {
        ESP_LOGCONFIG(TAG, "ATtiny85PWM initialised");
        ESP_LOGCONFIG(TAG, "  PWM Frequency: %u Hz", this->frequency_);
      }
}

void ATtiny85I2C::write_state(float state) {
  dc_ = state;
  uint8_t send [3];
  send[0] = dc_ * 100;
  send[1] = frequency_;
  send[2] = frequency_ >> 8;
  if (!this->write(send, 3)) {
    ESP_LOGV(TAG, "  PWM Frequency: %u Hz  DutyCicle: %u", this->frequency_, static_cast<uint8_t>(dc_ * 100));
  } else {
    ESP_LOGE(TAG, "Failed to send new State");
  }
}

void ATtiny85I2C::update_frequency(uint16_t frequency) {
  frequency_ = frequency;
  uint8_t send [3];
  send[0] = dc_ * 100;
  send[1] = frequency_;
  send[2] = frequency_ >> 8;
  if (!this->write(send, 3)) {
    ESP_LOGV(TAG, "PWM Frequency: %u Hz  DutyCicle: %u", this->frequency_, static_cast<uint8_t>(dc_ * 100));
  } else {
    ESP_LOGE(TAG, "Failed to send new State");
    ESP_LOGV(TAG, "Faild to send PWM Frequency: %u Hz  DutyCicle: %u", this->frequency_, static_cast<uint8_t>(dc_ * 100));
  }
}

}  // namespace attiny85_i2c
}  // namespace esphome
