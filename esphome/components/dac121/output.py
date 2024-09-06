import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.components import i2c
from esphome.const import (
     CONF_ID
)
#define PDM_NORMAL		0b00
#define PDM_2_5K_GND	0b01
#define PDM_100K_GND	0b10
#define PDM_HIGH_IMP	0b11


DEPENDENCIES = ["i2c"]
MULTI_CONF = True


dac121_ns = cg.esphome_ns.namespace("dac121")
DAC121 = dac121_ns.class_("DAC121", cg.Component, output.FloatOutput, i2c.I2CDevice)
POWERDOWNMODES = {
    "PDM_NORMAL": 0b00,
    "PDM_2_5K_GND": 0b01,
    "PDM_100K_GND": 0b10,
    "PDM_HIGH_IMP": 0b11
}

CONF_DAC121_ID = "dac121_id"
CONF_POWERDOWNMODE = "power_down_mode"

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend(
    {
        cv.Required(CONF_ID): cv.use_id(DAC121),
        cv.Optional(CONF_POWERDOWNMODE, default="PDM_NORMAL"): cv.one_of(
            *POWERDOWNMODES, upper=True, space="_"
        )
    }
    
).extend(cv.COMPONENT_SCHEMA).extend(i2c.i2c_device_schema(0x09))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    await output.register_output(var, config)
    cg.add(var.set_initial_PDM(POWERDOWNMODES[config.get[CONF_POWERDOWNMODE]]))
    return var
