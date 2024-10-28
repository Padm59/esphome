#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace multimodul_attiny85 {

class MultiModulATtiny85Output;
class MultiModulATtiny85Select;

class MultiModulATtiny85Component : public Component, public i2c::I2CDevice {
 public:
  MultiModulATtiny85Component();

  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

 protected:
  friend MultiModulATtiny85Output;
  friend MultiModulATtiny85Select;


 private:
};

}  // namespace multimodul_attiny85
}  // namespace esphome
