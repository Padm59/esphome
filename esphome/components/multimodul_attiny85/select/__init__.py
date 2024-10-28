import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import select
from esphome.const import  CONF_ID
from .. import MultiModulATtiny85Component, CONF_MULTIMODULATTINY85_ID, multimodul_attiny85_ns



DEPENDENCIES = ["multimodul_attiny85"]
CODEOWNERS = ["@Padm59"]


MultiModulATtiny85Select = multimodul_attiny85_ns.class_("MultiModulATtiny85Select", select.Select)



CONFIG_SCHEMA = select.SELECT_SCHEMA.extend ( {
    cv.Required(CONF_ID): cv.declare_id(MultiModulATtiny85Select),
    cv.GenerateID(CONF_MULTIMODULATTINY85_ID): cv.use_id(MultiModulATtiny85Component),
        
}
)
   

async def to_code(config):
    paren = await cg.get_variable(config[CONF_MULTIMODULATTINY85_ID])
    var = cg.new_Pvariable(
        config[CONF_ID],
        paren,
    )
    await select.register_select(var, config, options=["on", "off", "blink_fast", "blink_slow", "flash", "flash_once", "error"])
