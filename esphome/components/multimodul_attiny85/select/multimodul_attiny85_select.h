#pragma once

#include <utility>
#include <vector>

#include "../multimodul_attiny85.h"
#include "esphome/components/select/select.h"
#include "esphome/core/component.h"

namespace esphome {
namespace multimodul_attiny85 {

enum STATUS_LED
{
  STATUS_LED_off        = 0,
  STATUS_LED_on         = 1,
  STATUS_LED_blink_fast = 2,
  STATUS_LED_blink_slow = 3,
  STATUS_LED_flash      = 4,
  STATUS_LED_flash_once = 5,
  STATUS_LED_error      = 6
}

class MultiModulATtiny85Select : public select::Select {
 public:
  MultiModulATtiny85Select(MultiModulATtiny85Component *parent) : parent_(parent){}

  
 protected:
  MultiModulATtiny85Component *parent_
  
  void control(const std::string &value) override;
  uint8_t mapStatusToInt(const std::string& str);

};

}  // namespace multimodul_attiny85
}  // namespace esphome
