# pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/helpers.h"
#include "esphome/components/output/float_output.h"


namespace esphome {
namespace dac121 {

class DAC121 : public output::FloatOutput, public i2c::I2CDevice {
  public:
  
}

} // namespace dac121
} // namespace esphome
