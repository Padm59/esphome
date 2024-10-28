import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID, CONF_FREQUENCY
from .. import MultiModulATtiny85Component, CONF_MULTIMODULATTINY85_ID, multimodul_attiny85_ns

DEPENDENCIES = ["multimodul_attiny85"]

MultiModulATtiny85Output = multimodul_attiny85_ns.class_("MultiModulATtiny85Output", output.FloatOutput)


CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend(
    {
        cv.Required(CONF_ID): cv.declare_id(MultiModulATtiny85Output),
        cv.GenerateID(CONF_MULTIMODULATTINY85_ID): cv.use_id(MultiModulATtiny85Component),
    }
)


async def to_code(config):
    paren = await cg.get_variable(config[CONF_MULTIMODULATTINY85_ID])
    var = cg.new_Pvariable(
        config[CONF_ID],
        paren,
    )
    await output.register_output(var, config)
