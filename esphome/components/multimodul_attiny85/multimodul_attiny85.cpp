#include "multimodul_attiny85.h"

#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace multimodul_attiny85 {

static const char *const TAG = "multimodul_attiny85";

void MultiModulATtiny85Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up MultiModul ATtiny85 (0x%02X)...", this->address_);
  auto err = this->write(nullptr, 0);
  if (err != i2c::ERROR_OK) {
    this->mark_failed();
    return;
  }
}

void MultiModulATtiny85Component::dump_config() {
  ESP_LOGCONFIG(TAG, "MultiModul ATtiny85:");
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with MultiModul ATtiny85 failed!");
  }
}



}  // namespace multimodul_attiny85
}  // namespace esphome
