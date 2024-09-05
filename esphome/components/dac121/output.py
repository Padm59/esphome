import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.components import i2c
from esphome.const import CONF_CHANNEL, CONF_ID
from . import DAC121Output



DEPENDENCIES = ["i2c"]
MULTI_CONF = True


dac121_ns = cg.esphome_ns.namespace("dac121")
DAC121 = dac121_ns.class_("DAC121", output.FloatOutput, cg.Component)
CONF_DAC121_ID = "dac121_id"

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend(
    {
        cv.GenerateID(CONF_DAC121_ID): cv.use_id(DAC121Output),
    }
    
).extend(cv.COMPONENT_SCHEMA).extend(i2c.i2c_device_schema(0x09))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    await output.register_output(var, config)
    return var
