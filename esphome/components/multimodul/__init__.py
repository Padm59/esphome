import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.automation import maybe_simple_id
from esphome.components import number
from esphome.components import switch
from esphome.components import mcp4728
from esphome.components.mcp4728 import output as mcp4728_output
from esphome.components import output
import esphome.components.attiny85_i2c.output as attiny85_i2c_output


AUTO_LOAD = ["number", "switch", "mcp4728", "tca9548a", "output", "attiny85_i2c"]
DEPENDENCIES = ["i2c"]


multimodul_ns = cg.esphome_ns.namespace("multimodul")
MultiModul = multimodul_ns.class_("MultiModul", cg.Component)

MultiModulAttiny85 = multimodul_ns.class_("MultiModulATtiny85", attiny85_i2c_output.ATtiny85I2C, cg.Component)
MultiModulMCPComp = multimodul_ns.class_("MultiModulMCPCom", mcp4728.MCP4728Component, cg.Component)
MultiModulMCPOut = multimodul_ns.class_("MultiModulMCPOut", mcp4728_output.MCP4728Channel, cg.Component)
