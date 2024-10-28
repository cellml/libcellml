# The content of this file was generated using the Python profile of libCellML 0.6.1.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.6.1"

STATE_COUNT = 4
VARIABLE_COUNT = 17


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


def initialise_variables(states, rates, variables):
    variables[3] = 12.0
    variables[4] = 0.075
    variables[5] = -60.0
    variables[7] = 400.0
    variables[8] = 40.0
    states[0] = -87.0
    states[1] = 0.01
    states[2] = 0.8
    states[3] = 0.01


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    variables[6] = pow(states[1], 3.0)*states[2]*variables[7]
    variables[0] = (variables[6]+0.14)*(states[0]-variables[8])
    variables[1] = variables[4]*(states[0]-variables[5])
    variables[13] = 1.2*exp((-states[0]-90.0)/50.0)+0.015*exp((states[0]+90.0)/60.0)
    variables[14] = 1.2*pow(states[3], 4.0)
    variables[2] = (variables[13]+variables[14])*(states[0]+100.0)
    rates[0] = -(variables[0]+variables[2]+variables[1])/variables[3]
    variables[9] = 0.1*(-states[0]-48.0)/(exp((-states[0]-48.0)/15.0)-1.0)
    variables[10] = 0.12*(states[0]+8.0)/(exp((states[0]+8.0)/5.0)-1.0)
    rates[1] = variables[9]*(1.0-states[1])-variables[10]*states[1]
    variables[11] = 0.17*exp((-states[0]-90.0)/20.0)
    variables[12] = 1.0/(1.0+exp((-states[0]-42.0)/10.0))
    rates[2] = variables[11]*(1.0-states[2])-variables[12]*states[2]
    variables[15] = 0.0001*(-states[0]-50.0)/(exp((-states[0]-50.0)/10.0)-1.0)
    variables[16] = 0.002*exp((-states[0]-90.0)/80.0)
    rates[3] = variables[15]*(1.0-states[3])-variables[16]*states[3]


def compute_variables(voi, states, rates, variables):
    variables[1] = variables[4]*(states[0]-variables[5])
    variables[6] = pow(states[1], 3.0)*states[2]*variables[7]
    variables[0] = (variables[6]+0.14)*(states[0]-variables[8])
    variables[9] = 0.1*(-states[0]-48.0)/(exp((-states[0]-48.0)/15.0)-1.0)
    variables[10] = 0.12*(states[0]+8.0)/(exp((states[0]+8.0)/5.0)-1.0)
    variables[11] = 0.17*exp((-states[0]-90.0)/20.0)
    variables[12] = 1.0/(1.0+exp((-states[0]-42.0)/10.0))
    variables[13] = 1.2*exp((-states[0]-90.0)/50.0)+0.015*exp((states[0]+90.0)/60.0)
    variables[14] = 1.2*pow(states[3], 4.0)
    variables[2] = (variables[13]+variables[14])*(states[0]+100.0)
    variables[15] = 0.0001*(-states[0]-50.0)/(exp((-states[0]-50.0)/10.0)-1.0)
    variables[16] = 0.002*exp((-states[0]-90.0)/80.0)
