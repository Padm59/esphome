import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID

CODEOWNERS = ["@Padm59"]
DEPENDENCIES = ["i2c"]
MULTI_CONF = True


multimodul_attiny85_ns = cg.esphome_ns.namespace("multimodul_attiny85")
MultiModulATtiny85Component = multimodul_attiny85_ns.class_("MultiModulATtiny85Component", cg.Component, i2c.I2CDevice)
CONF_MULTIMODULATTINY85_ID = "multimodul_attiny85_id"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(MultiModulATtiny85Component)
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x21))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
