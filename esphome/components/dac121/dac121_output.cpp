#include <dac121_output.h>
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

// already defined in the header file
// #define DATA_MASK       0b111111111111
// #define PDM_MASK		0b11 << 12

// #define PDM_NORMAL		0b00
// #define PDM_2_5K_GND	0b01
// #define PDM_100K_GND	0b10
// #define PDM_HIGH_IMP	0b11

namespace esphome {
namespace dac121 {

static const char *const TAG = "dac121";

void DAC121::setup() {
  ESP_LOGCONFIG(TAG, "Setting up DAC121Output...");
  ESP_LOGV(TAG, "Resetting device...");

  uint16_t maskedMode = (this->pdm_ << 12) & PDM_MASK;
  uint16_t maskedData = this->data_ & DATA_MASK;  
  uint16_t value = maskedData | maskedMode;
  uint8_t send[2];
  this->uint16_to_array(value, send);
  if(!this->write(send, 2)) {
    ESP_LOGE(TAG, "Reset failed");
    this->mark_failed();
    return;
  } else {
    ESP_LOGV(TAG, "Reset succeeded");
  }
  
}

void DAC121::dump_config() {
    if (this->is_failed()) {
        ESP_LOGE(TAG, "Setting up DAC121 failed!");
    } else {
        ESP_LOGCONFIG(TAG, "DAC121 initialised");
  }
}

void DAC121::write_state(float state) {
  this->data_ = 4095 * state;
  uint16_t maskedMode = (this->pdm_ << 12) & PDM_MASK;
  uint16_t maskedData = this->data_ & DATA_MASK;
  uint16_t value = maskedData | maskedMode;
  uint8_t send[2];
  this->uint16_to_array(value, send);
  if(this->write(send, 2)) {
    ESP_LOGV(TAG, "Data send")
  } else {
    ESP_LOGE(TAG, "Failed to send new State")
  }
}

void DAC121::uint16_to_array(uint16_t value, uint8_t *array) {
  array[0] = (uint8_t) (value >> 8);    // Höheres Byte
  array[1] = (uint8_t) (value & 0xFF);  // Niedrigeres Byte
}

// uint8_t DAC121::get_PDM_bits(PowerDownMode mode) {
//   switch (mode) {
//     case enum_PDM_NORMAL:
//       return PDM_NORMAL;
//       break;
//     case enum_PDM_2_5K_GND:
//       return PDM_2_5K_GND;
//       break;
//     case enum_PDM_100K_GND:
//       return PDM_100K_GND;
//       break;
//     case enum_PDM_HIGH_IMP:
//       return PDM_HIGH_IMP;
//       break;
//     default:
//       return PDM_NORMAL;
//       break;
//   }
// }

}  // namespace dac121
}  // namespace esphome
