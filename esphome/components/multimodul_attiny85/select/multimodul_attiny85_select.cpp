#include "multimodul_attiny85_select.h"
#include "esphome/core/log.h"

namespace esphome {
namespace multimodul_attiny85 {

static const char *const TAG = "multimodul_attiny85_select";

void MultiModulATtiny85Select::control(const std::string &value) {
  this->publish_state(value);
  
  uint8_t data = mapStatusToInt(value);
  if (data != -1) {
    if (data != STATUS_LED_flash_once){
      this->publish_state(value);
      if (!parent_->write(&data, 1)) {
      ESP_LOGV(TAG, "StatusLED gesetzt: %s", value);
      } else {
      ESP_LOGE(TAG, "Failed to send new StatusLED state: %s", value);
      }
    }else {
      if (!parent_->write(&data, 1)) {
      ESP_LOGV(TAG, "StatusLED gesetzt: %s", value);
      } else {
      ESP_LOGE(TAG, "Failed to send new StatusLED state: %s", value);
      }
    }
  }

}

uint8_t MultiModulATtiny85Select::mapStatusToInt(const std::string &str) { 
    if (str == "off") return STATUS_LED_off;
    if (str == "on") return STATUS_LED_on;
    if (str == "blink_fast") return STATUS_LED_blink_fast;
    if (str == "blink_slow") return STATUS_LED_blink_slow;
    if (str == "flash") return STATUS_LED_flash;
    if (str == "flash_once") return STATUS_LED_flash_once;
    if (str == "error") return STATUS_LED_error;
    return -1;

}

}  // namespace multimodul_attiny85
}  // namespace esphome
