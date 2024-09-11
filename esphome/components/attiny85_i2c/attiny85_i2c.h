# pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace attiny85_i2c {


class ATtiny85I2C : public Component, public i2c::I2CDevice {
  public:
    void setup() override;
    void dump_config() override;
    float get_setup_priority() const override { return setup_priority::HARDWARE; };

  protected:

};

} // namespace attiny85_i2c
} // namespace esphome
