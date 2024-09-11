# pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/helpers.h"
#include "esphome/core/hal.h"
#include "esphome/core/automation.h"
#include "esphome/components/output/float_output.h"

namespace esphome {
namespace attiny85_i2c {


class ATtiny85I2C : public Component, public output::FloatOutput, public i2c::I2CDevice {
  public:
    void  setup() override;
    void  dump_config() override;
    float get_setup_priority() const override { return setup_priority::HARDWARE; }

    void  set_frequency(uint16_t frequency) {this->frequency_ = frequency; }

    void write_state(float state) override;
    void  update_frequency(uint16_t frequency);

  protected:

    uint16_t  frequency_ = 100;
    float     dc_ = 0;
};

template<typename... Ts> class SetFrequencyAction : public Action<Ts...> {
 public:
  SetFrequencyAction(LEDCOutput *parent) : parent_(parent) {}
  TEMPLATABLE_VALUE(uint16_t, frequency);

  void play(Ts... x) {
    uint16_t freq = this->frequency_.value(x...);
    this->parent_->update_frequency(freq);
  }

 protected:
  ATtiny85I2C *parent_;
};


} // namespace attiny85_i2c
} // namespace esphome
