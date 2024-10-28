#pragma once

#include "../multimodul_attiny85.h"
#include "esphome/core/component.h"
#include "esphome/components/output/float_output.h"
#include "esphome/core/helpers.h"
#include "esphome/core/hal.h"
#include "esphome/core/automation.h"

namespace esphome {
namespace multimodul_attiny85 {

class MultiModulATtiny85Output : public output::FloatOutput {
 public:
  MultiModulATtiny85Output(MultiModulATtiny85Component *parent) : parent_(parent) {}

  void write_state(float state) override;
  void  update_frequency(uint16_t frequency);
  


 protected:
  MultiModulATtiny85Component *parent_;
  uint16_t  frequency_ = 100;
  float     dc_ = 0;

};


template<typename... Ts> class SetFrequencyAction : public Action<Ts...> {
 public:
  SetFrequencyAction(MultiModulATtiny85Output *parent) : parent_(parent) {}
  TEMPLATABLE_VALUE(uint16_t, frequency);

  void play(Ts... x) {
    uint16_t freq = this->frequency_.value(x...);
    this->parent_->update_frequency(freq);
  }
  
 protected:
  MultiModulATtiny85Component *parent_;
};

}  // namespace multimodul_attiny85
}  // namespace esphome
