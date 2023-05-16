# The content of this file was generated using the Python profile of libCellML 0.4.0.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.4.0"

STATE_COUNT = 4
VARIABLE_COUNT = 18


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4
    EXTERNAL = 5


VOI_INFO = {"name": "time", "units": "millisecond", "component": "environment", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "V", "units": "millivolt", "component": "membrane", "type": VariableType.STATE},
    {"name": "h", "units": "dimensionless", "component": "sodium_channel_h_gate", "type": VariableType.STATE},
    {"name": "m", "units": "dimensionless", "component": "sodium_channel_m_gate", "type": VariableType.STATE},
    {"name": "n", "units": "dimensionless", "component": "potassium_channel_n_gate", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "i_Stim", "units": "microA_per_cm2", "component": "membrane", "type": VariableType.ALGEBRAIC},
    {"name": "i_L", "units": "microA_per_cm2", "component": "leakage_current", "type": VariableType.ALGEBRAIC},
    {"name": "i_K", "units": "microA_per_cm2", "component": "potassium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "i_Na", "units": "microA_per_cm2", "component": "sodium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "Cm", "units": "microF_per_cm2", "component": "membrane", "type": VariableType.EXTERNAL},
    {"name": "E_R", "units": "millivolt", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "E_L", "units": "millivolt", "component": "leakage_current", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_L", "units": "milliS_per_cm2", "component": "leakage_current", "type": VariableType.CONSTANT},
    {"name": "E_Na", "units": "millivolt", "component": "sodium_channel", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_Na", "units": "milliS_per_cm2", "component": "sodium_channel", "type": VariableType.CONSTANT},
    {"name": "alpha_m", "units": "per_millisecond", "component": "sodium_channel_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_m", "units": "per_millisecond", "component": "sodium_channel_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_h", "units": "per_millisecond", "component": "sodium_channel_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_h", "units": "per_millisecond", "component": "sodium_channel_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "E_K", "units": "millivolt", "component": "potassium_channel", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "g_K", "units": "milliS_per_cm2", "component": "potassium_channel", "type": VariableType.CONSTANT},
    {"name": "alpha_n", "units": "per_millisecond", "component": "potassium_channel_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_n", "units": "per_millisecond", "component": "potassium_channel_n_gate", "type": VariableType.ALGEBRAIC}
]


def leq_func(x, y):
    return 1.0 if x <= y else 0.0


def geq_func(x, y):
    return 1.0 if x >= y else 0.0


def and_func(x, y):
    return 1.0 if bool(x) & bool(y) else 0.0


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(voi, states, variables, external_variable):
    variables[5] = 0.0
    variables[7] = 0.3
    variables[9] = 120.0
    variables[15] = 36.0
    states[0] = 0.0
    states[1] = 0.6
    states[2] = 0.05
    states[3] = 0.325
    variables[4] = external_variable(voi, states, variables, 4)


def compute_computed_constants(variables):
    variables[6] = variables[5]-10.613
    variables[8] = variables[5]-115.0
    variables[14] = variables[5]+12.0


def compute_rates(voi, states, rates, variables, external_variable):
    variables[0] = -20.0 if and_func(geq_func(voi, 10.0), leq_func(voi, 10.5)) else 0.0
    variables[4] = external_variable(voi, states, variables, 4)
    variables[1] = variables[7]*(states[0]-variables[6])
    variables[2] = variables[15]*pow(states[3], 4.0)*(states[0]-variables[14])
    variables[3] = variables[9]*pow(states[2], 3.0)*states[1]*(states[0]-variables[8])
    rates[0] = -(-variables[0]+variables[3]+variables[2]+variables[1])/variables[4]
    variables[10] = 0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0)
    variables[11] = 4.0*exp(states[0]/18.0)
    rates[2] = variables[10]*(1.0-states[2])-variables[11]*states[2]
    variables[12] = 0.07*exp(states[0]/20.0)
    variables[13] = 1.0/(exp((states[0]+30.0)/10.0)+1.0)
    rates[1] = variables[12]*(1.0-states[1])-variables[13]*states[1]
    variables[16] = 0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0)
    variables[17] = 0.125*exp(states[0]/80.0)
    rates[3] = variables[16]*(1.0-states[3])-variables[17]*states[3]


def compute_variables(voi, states, rates, variables, external_variable):
    variables[1] = variables[7]*(states[0]-variables[6])
    variables[3] = variables[9]*pow(states[2], 3.0)*states[1]*(states[0]-variables[8])
    variables[10] = 0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0)
    variables[11] = 4.0*exp(states[0]/18.0)
    variables[12] = 0.07*exp(states[0]/20.0)
    variables[13] = 1.0/(exp((states[0]+30.0)/10.0)+1.0)
    variables[2] = variables[15]*pow(states[3], 4.0)*(states[0]-variables[14])
    variables[16] = 0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0)
    variables[17] = 0.125*exp(states[0]/80.0)
    variables[4] = external_variable(voi, states, variables, 4)
