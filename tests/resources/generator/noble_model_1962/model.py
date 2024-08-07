# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 4
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 17


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "time", "units": "millisecond", "component": "environment", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "V", "units": "millivolt", "component": "membrane", "type": VariableType.STATE},
    {"name": "m", "units": "dimensionless", "component": "sodium_channel_m_gate", "type": VariableType.STATE},
    {"name": "h", "units": "dimensionless", "component": "sodium_channel_h_gate", "type": VariableType.STATE},
    {"name": "n", "units": "dimensionless", "component": "potassium_channel_n_gate", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "i_Na", "units": "microA_per_cm2", "component": "sodium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "i_Leak", "units": "microA_per_cm2", "component": "leakage_current", "type": VariableType.ALGEBRAIC},
    {"name": "i_K", "units": "microA_per_cm2", "component": "potassium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "Cm", "units": "microF_per_cm2", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "g_L", "units": "milliS_per_cm2", "component": "leakage_current", "type": VariableType.CONSTANT},
    {"name": "E_L", "units": "millivolt", "component": "leakage_current", "type": VariableType.CONSTANT},
    {"name": "g_Na", "units": "milliS_per_cm2", "component": "sodium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "g_Na_max", "units": "milliS_per_cm2", "component": "sodium_channel", "type": VariableType.CONSTANT},
    {"name": "E_Na", "units": "millivolt", "component": "sodium_channel", "type": VariableType.CONSTANT},
    {"name": "alpha_m", "units": "per_millisecond", "component": "sodium_channel_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_m", "units": "per_millisecond", "component": "sodium_channel_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_h", "units": "per_millisecond", "component": "sodium_channel_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_h", "units": "per_millisecond", "component": "sodium_channel_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "g_K1", "units": "milliS_per_cm2", "component": "potassium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "g_K2", "units": "milliS_per_cm2", "component": "potassium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_n", "units": "per_millisecond", "component": "potassium_channel_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_n", "units": "per_millisecond", "component": "potassium_channel_n_gate", "type": VariableType.ALGEBRAIC}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, rates, constants):
    constants[3] = 12.0
    constants[4] = 0.075
    constants[5] = -60.0
    constants[7] = 400.0
    constants[8] = 40.0
    states[0] = -87.0
    states[1] = 0.01
    states[2] = 0.8
    states[3] = 0.01


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[6] = pow(states[1], 3.0)*states[2]*constants[7]
    algebraic[0] = (algebraic[6]+0.14)*(states[0]-constants[8])
    algebraic[1] = constants[4]*(states[0]-constants[5])
    algebraic[13] = 1.2*exp((-states[0]-90.0)/50.0)+0.015*exp((states[0]+90.0)/60.0)
    algebraic[14] = 1.2*pow(states[3], 4.0)
    algebraic[2] = (algebraic[13]+algebraic[14])*(states[0]+100.0)
    rates[0] = -(algebraic[0]+algebraic[2]+algebraic[1])/constants[3]
    algebraic[9] = 0.1*(-states[0]-48.0)/(exp((-states[0]-48.0)/15.0)-1.0)
    algebraic[10] = 0.12*(states[0]+8.0)/(exp((states[0]+8.0)/5.0)-1.0)
    rates[1] = algebraic[9]*(1.0-states[1])-algebraic[10]*states[1]
    algebraic[11] = 0.17*exp((-states[0]-90.0)/20.0)
    algebraic[12] = 1.0/(1.0+exp((-states[0]-42.0)/10.0))
    rates[2] = algebraic[11]*(1.0-states[2])-algebraic[12]*states[2]
    algebraic[15] = 0.0001*(-states[0]-50.0)/(exp((-states[0]-50.0)/10.0)-1.0)
    algebraic[16] = 0.002*exp((-states[0]-90.0)/80.0)
    rates[3] = algebraic[15]*(1.0-states[3])-algebraic[16]*states[3]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[1] = constants[4]*(states[0]-constants[5])
    algebraic[6] = pow(states[1], 3.0)*states[2]*constants[7]
    algebraic[0] = (algebraic[6]+0.14)*(states[0]-constants[8])
    algebraic[9] = 0.1*(-states[0]-48.0)/(exp((-states[0]-48.0)/15.0)-1.0)
    algebraic[10] = 0.12*(states[0]+8.0)/(exp((states[0]+8.0)/5.0)-1.0)
    algebraic[11] = 0.17*exp((-states[0]-90.0)/20.0)
    algebraic[12] = 1.0/(1.0+exp((-states[0]-42.0)/10.0))
    algebraic[13] = 1.2*exp((-states[0]-90.0)/50.0)+0.015*exp((states[0]+90.0)/60.0)
    algebraic[14] = 1.2*pow(states[3], 4.0)
    algebraic[2] = (algebraic[13]+algebraic[14])*(states[0]+100.0)
    algebraic[15] = 0.0001*(-states[0]-50.0)/(exp((-states[0]-50.0)/10.0)-1.0)
    algebraic[16] = 0.002*exp((-states[0]-90.0)/80.0)
