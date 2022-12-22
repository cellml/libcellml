# The content of this file was generated using the Python profile of libCellML 0.4.0.

from enum import Enum
from math import *


__version__ = "0.3.2"
LIBCELLML_VERSION = "0.4.0"

STATE_COUNT = 2
VARIABLE_COUNT = 20


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4
    EXTERNAL = 5


VOI_INFO = {"name": "time", "units": "millisecond", "component": "environment", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "h", "units": "dimensionless", "component": "sodium_channel_h_gate", "type": VariableType.STATE},
    {"name": "n", "units": "dimensionless", "component": "potassium_channel_n_gate", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "m", "units": "dimensionless", "component": "sodium_channel_m_gate", "type": VariableType.EXTERNAL},
    {"name": "V", "units": "millivolt", "component": "membrane", "type": VariableType.EXTERNAL},
    {"name": "i_Stim", "units": "microA_per_cm2", "component": "membrane", "type": VariableType.ALGEBRAIC},
    {"name": "E_L", "units": "millivolt", "component": "leakage_current", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "i_L", "units": "microA_per_cm2", "component": "leakage_current", "type": VariableType.ALGEBRAIC},
    {"name": "E_Na", "units": "millivolt", "component": "sodium_channel", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "i_Na", "units": "microA_per_cm2", "component": "sodium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_m", "units": "per_millisecond", "component": "sodium_channel_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_m", "units": "per_millisecond", "component": "sodium_channel_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_h", "units": "per_millisecond", "component": "sodium_channel_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_h", "units": "per_millisecond", "component": "sodium_channel_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "E_K", "units": "millivolt", "component": "potassium_channel", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "i_K", "units": "microA_per_cm2", "component": "potassium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_n", "units": "per_millisecond", "component": "potassium_channel_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_n", "units": "per_millisecond", "component": "potassium_channel_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "Cm", "units": "microF_per_cm2", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "E_R", "units": "millivolt", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "g_L", "units": "milliS_per_cm2", "component": "leakage_current", "type": VariableType.CONSTANT},
    {"name": "g_Na", "units": "milliS_per_cm2", "component": "sodium_channel", "type": VariableType.CONSTANT},
    {"name": "g_K", "units": "milliS_per_cm2", "component": "potassium_channel", "type": VariableType.CONSTANT}
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
    variables[15] = 1.0
    variables[16] = 0.0
    variables[17] = 0.3
    variables[18] = 120.0
    variables[19] = 36.0
    states[0] = 0.6
    states[1] = 0.325
    variables[1] = external_variable(voi, states, variables, 1)
    variables[0] = external_variable(voi, states, variables, 0)


def compute_computed_constants(variables):
    variables[3] = variables[16]-10.613
    variables[5] = variables[16]-115.0
    variables[11] = variables[16]+12.0


def compute_rates(voi, states, rates, variables, external_variable):
    variables[1] = external_variable(voi, states, variables, 1)
    variables[9] = 0.07*exp(variables[1]/20.0)
    variables[10] = 1.0/(exp((variables[1]+30.0)/10.0)+1.0)
    rates[0] = variables[9]*(1.0-states[0])-variables[10]*states[0]
    variables[13] = 0.01*(variables[1]+10.0)/(exp((variables[1]+10.0)/10.0)-1.0)
    variables[14] = 0.125*exp(variables[1]/80.0)
    rates[1] = variables[13]*(1.0-states[1])-variables[14]*states[1]


def compute_variables(voi, states, rates, variables, external_variable):
    variables[1] = external_variable(voi, states, variables, 1)
    variables[0] = external_variable(voi, states, variables, 0)
    variables[2] = -20.0 if and_func(geq_func(voi, 10.0), leq_func(voi, 10.5)) else 0.0
    variables[4] = variables[17]*(variables[1]-variables[3])
    variables[6] = variables[18]*pow(variables[0], 3.0)*states[0]*(variables[1]-variables[5])
    variables[7] = 0.1*(variables[1]+25.0)/(exp((variables[1]+25.0)/10.0)-1.0)
    variables[8] = 4.0*exp(variables[1]/18.0)
    variables[12] = variables[19]*pow(states[1], 4.0)*(variables[1]-variables[11])
