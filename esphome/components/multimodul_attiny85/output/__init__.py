import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import output
from esphome.const import CONF_ID, CONF_FREQUENCY
from .. import MultiModulATtiny85Component, CONF_MULTIMODULATTINY85_ID, multimodul_attiny85_ns

DEPENDENCIES = ["multimodul_attiny85"]
CODEOWNERS = ["@Padm59"]

MultiModulATtiny85Output = multimodul_attiny85_ns.class_("MultiModulATtiny85Output", output.FloatOutput)
SetFrequencyAction = multimodul_attiny85_ns.class_("SetFrequencyAction", automation.Action)


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



@automation.register_action(
    "output.ledc.set_frequency",
    SetFrequencyAction,
    cv.Schema(
        {
            cv.Required(CONF_ID): cv.use_id(MultiModulATtiny85Output),
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