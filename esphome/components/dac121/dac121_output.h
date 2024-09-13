# pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/helpers.h"
#include "esphome/components/output/float_output.h"

#define DATA_MASK     0b111111111111
#define PDM_MASK		  0b11 << 12

#define PDM_NORMAL		0b00
#define PDM_2_5K_GND	0b01
#define PDM_100K_GND	0b10
#define PDM_HIGH_IMP	0b11


namespace esphome {
namespace dac121 {

enum PowerDownMode {enum_PDM_NORMAL = 0, enum_PDM_2_5K_GND, enum_PDM_100K_GND, enum_PDM_HIGH_IMP};

class DAC121 : public Component, public output::FloatOutput, public i2c::I2CDevice {
  public:
    void setup() override;
    void dump_config() override;
    float get_setup_priority() const override { return setup_priority::HARDWARE; };

    void set_initial_PDM(uint8_t pdm) {pdm_ = pdm;};

  protected:
    void write_state(float state) override;

    void uint16_to_array(uint16_t value, uint8_t* array);
    
    uint8_t pdm_;
    uint16_t data_ = 0;
};

} // namespace dac121
} // namespace esphome
