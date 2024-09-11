import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import i2c
from esphome.components import output
from esphome.const import (
    CONF_FREQUENCY,
    CONF_ID
)

CODEOWNERS = ["@Padm59"]
#vlt umbenennen, auf attiny85pwm oder so falls die übergeordnete komponente attiny85_i2c nicht weiter entwickelt wird

def validate_frequency(value):
    value = cv.frequency(value)
    min_freq = 1
    max_freq = 10000
    if value < min_freq:
        raise cv.Invalid(
            f"This frequency setting is not possible, please choose a higher frequency (at least {int(min_freq)}Hz)"
        )
    if value > max_freq:
        raise cv.Invalid(
            f"This frequency setting is not possible, please choose a lower frequency (at most {int(max_freq)}Hz)"
        )
    return value


attiny85_i2c_ns = cg.esphome_ns.namespace("attiny85_i2c")
ATtiny85I2C = attiny85_i2c_ns.class_("ATtiny85I2C", output.FloatOutput, cg.Component)
SetFrequencyAction = attiny85_i2c_ns.class_("SetFrequencyAction", automation.Action)

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend(
    {
        cv.Required(CONF_ID): cv.declare_id(ATtiny85I2C),
        cv.Optional(CONF_FREQUENCY, default="100Hz"): cv.frequency,
    }
).extend(cv.COMPONENT_SCHEMA).extend(i2c.i2c_device_schema(0x21))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await output.register_output(var, config)
    await i2c.register_i2c_device(var, config)
    cg.add(var.set_frequency(config[CONF_FREQUENCY]))


@automation.register_action(
    "output.ledc.set_frequency",
    SetFrequencyAction,
    cv.Schema(
        {
            cv.Required(CONF_ID): cv.use_id(ATtiny85I2C),
            cv.Required(CONF_FREQUENCY): cv.templatable(validate_frequency),
        }
    ),
)
async def ledc_set_frequency_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, paren)
    template_ = await cg.templatable(config[CONF_FREQUENCY], args, int)
    cg.add(var.set_frequency(template_))
    return var