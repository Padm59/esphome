#include "multimodul_attiny85_output.h"

#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace multimodul_attiny85 {

void MultiModulATtiny85Output::write_state(float state) {
  dc_ = state;
  uint8_t send [3];
  send[0] = dc_ * 100;
  send[1] = frequency_;
  send[2] = frequency_ >> 8;
  if (!parent_->write(send, 3)) {
    ESP_LOGV(TAG, "  PWM Frequency: %u Hz  DutyCicle: %u", this->frequency_, static_cast<uint8_t>(dc_ * 100));
  } else {
    ESP_LOGE(TAG, "Failed to send new State");
  }
}

void MultiModulATtiny85Output::update_frequency(uint16_t frequency) {
  frequency_ = frequency;
  uint8_t send [3];
  send[0] = dc_ * 100;
  send[1] = frequency_;
  send[2] = frequency_ >> 8;
  if (!parent_->write(send, 3)) {
    ESP_LOGV(TAG, "PWM Frequency: %u Hz  DutyCicle: %u", this->frequency_, static_cast<uint8_t>(dc_ * 100));
  } else {
    ESP_LOGE(TAG, "Failed to send new State");
    ESP_LOGV(TAG, "Faild to send PWM Frequency: %u Hz  DutyCicle: %u", this->frequency_, static_cast<uint8_t>(dc_ * 100));
  }
}

}  // namespace multimodul_attiny85
}  // namespace esphome
