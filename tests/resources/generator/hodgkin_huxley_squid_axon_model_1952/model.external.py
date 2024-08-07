# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 3
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 19


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
    {"name": "m", "units": "dimensionless", "component": "sodium_channel_m_gate", "type": VariableType.STATE},
    {"name": "n", "units": "dimensionless", "component": "potassium_channel_n_gate", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "i_Stim", "units": "microA_per_cm2", "component": "membrane", "type": VariableType.ALGEBRAIC},
    {"name": "V", "units": "millivolt", "component": "membrane", "type": VariableType.EXTERNAL},
    {"name": "i_L", "units": "microA_per_cm2", "component": "leakage_current", "type": VariableType.ALGEBRAIC},
    {"name": "i_K", "units": "microA_per_cm2", "component": "potassium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "i_Na", "units": "microA_per_cm2", "component": "sodium_channel", "type": VariableType.EXTERNAL},
    {"name": "Cm", "units": "microF_per_cm2", "component": "membrane", "type": VariableType.CONSTANT},
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
    {"name": "alpha_n", "units": "per_millisecond", "component": "potassium_channel_n_gate", "type": VariableType.EXTERNAL},
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


def initialise_variables(voi, states, rates, constants, external_variable):
    constants[5] = 1.0
    constants[6] = 0.0
    constants[8] = 0.3
    constants[10] = 120.0
    constants[16] = 36.0
    states[0] = 0.6
    states[1] = 0.05
    states[2] = 0.325
    algebraic[1] = external_variable(voi, states, rates, variables, 1)
    algebraic[17] = external_variable(voi, states, rates, variables, 17)
    algebraic[4] = external_variable(voi, states, rates, variables, 4)


def compute_computed_constants(constants, computed_constants):
    computed_constants[7] = constants[6]-10.613
    computed_constants[9] = constants[6]-115.0
    computed_constants[15] = constants[6]+12.0


def compute_rates(voi, states, rates, constants, computed_constants, algebraic, external_variable):
    algebraic[1] = external_variable(voi, states, rates, variables, 1)
    algebraic[11] = 0.1*(algebraic[1]+25.0)/(exp((algebraic[1]+25.0)/10.0)-1.0)
    algebraic[12] = 4.0*exp(algebraic[1]/18.0)
    rates[1] = algebraic[11]*(1.0-states[1])-algebraic[12]*states[1]
    algebraic[13] = 0.07*exp(algebraic[1]/20.0)
    algebraic[14] = 1.0/(exp((algebraic[1]+30.0)/10.0)+1.0)
    rates[0] = algebraic[13]*(1.0-states[0])-algebraic[14]*states[0]
    algebraic[17] = external_variable(voi, states, rates, variables, 17)
    algebraic[18] = 0.125*exp(algebraic[1]/80.0)
    rates[2] = algebraic[17]*(1.0-states[2])-algebraic[18]*states[2]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic, external_variable):
    algebraic[0] = -20.0 if and_func(geq_func(voi, 10.0), leq_func(voi, 10.5)) else 0.0
    algebraic[1] = external_variable(voi, states, rates, variables, 1)
    algebraic[2] = constants[8]*(algebraic[1]-computed_constants[7])
    algebraic[17] = external_variable(voi, states, rates, variables, 17)
    algebraic[4] = external_variable(voi, states, rates, variables, 4)
    algebraic[3] = constants[16]*pow(states[2], 4.0)*(algebraic[1]-computed_constants[15])
