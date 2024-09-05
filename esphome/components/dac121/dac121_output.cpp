#include <dac121_output.h>

// #define DATA_MASK       0b111111111111
// #define PDM_MASK		0b11 << 12
// #define PDM_BIT_1_POS	13
// #define PDM_BIT_0_POS	12

// #define PDM_NORMAL		0b00
// #define PDM_2_5K_GND	0b01
// #define PDM_100K_GND	0b10
// #define PDM_HIGH_IMP	0b11


namespace esphome{
namespace dac121{

static const char *const TAG = "dac121";

void DAC121::setup() {}

}  // namespace dac121
} // namespace esphome

