# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 2
CONSTANT_COUNT = 5
COMPUTED_CONSTANT_COUNT = 3
ALGEBRAIC_COUNT = 10
EXTERNAL_COUNT = 2


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
    {"name": "Cm", "units": "microF_per_cm2", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "E_R", "units": "millivolt", "component": "membrane", "type": VariableType.CONSTANT},
    {"name": "g_L", "units": "milliS_per_cm2", "component": "leakage_current", "type": VariableType.CONSTANT},
    {"name": "g_Na", "units": "milliS_per_cm2", "component": "sodium_channel", "type": VariableType.CONSTANT},
    {"name": "g_K", "units": "milliS_per_cm2", "component": "potassium_channel", "type": VariableType.CONSTANT},
    {"name": "E_L", "units": "millivolt", "component": "leakage_current", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "E_Na", "units": "millivolt", "component": "sodium_channel", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "E_K", "units": "millivolt", "component": "potassium_channel", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "i_Stim", "units": "microA_per_cm2", "component": "membrane", "type": VariableType.ALGEBRAIC},
    {"name": "i_L", "units": "microA_per_cm2", "component": "leakage_current", "type": VariableType.ALGEBRAIC},
    {"name": "i_K", "units": "microA_per_cm2", "component": "potassium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "i_Na", "units": "microA_per_cm2", "component": "sodium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_m", "units": "per_millisecond", "component": "sodium_channel_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_m", "units": "per_millisecond", "component": "sodium_channel_m_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_h", "units": "per_millisecond", "component": "sodium_channel_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_h", "units": "per_millisecond", "component": "sodium_channel_h_gate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_n", "units": "per_millisecond", "component": "potassium_channel_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_n", "units": "per_millisecond", "component": "potassium_channel_n_gate", "type": VariableType.ALGEBRAIC},
    {"name": "V", "units": "millivolt", "component": "membrane", "type": VariableType.EXTERNAL},
    {"name": "m", "units": "dimensionless", "component": "sodium_channel_m_gate", "type": VariableType.EXTERNAL}
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
    constants[0] = 1.0
    constants[1] = 0.0
    constants[2] = 0.3
    constants[3] = 120.0
    constants[4] = 36.0
    states[0] = 0.6
    states[1] = 0.325
    algebraic[1] = external_variable(voi, states, rates, variables, 1)
    algebraic[5] = external_variable(voi, states, rates, variables, 5)


def compute_computed_constants(constants, computed_constants):
    computed_constants[0] = constants[1]-10.613
    computed_constants[1] = constants[1]-115.0
    computed_constants[2] = constants[1]+12.0


def compute_rates(voi, states, rates, constants, computed_constants, algebraic, external_variable):
    algebraic[1] = external_variable(voi, states, rates, variables, 1)
    algebraic[8] = 0.07*exp(algebraic[1]/20.0)
    algebraic[9] = 1.0/(exp((algebraic[1]+30.0)/10.0)+1.0)
    rates[0] = algebraic[8]*(1.0-states[0])-algebraic[9]*states[0]
    algebraic[10] = 0.01*(algebraic[1]+10.0)/(exp((algebraic[1]+10.0)/10.0)-1.0)
    algebraic[11] = 0.125*exp(algebraic[1]/80.0)
    rates[1] = algebraic[10]*(1.0-states[1])-algebraic[11]*states[1]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic, external_variable):
    algebraic[0] = -20.0 if and_func(geq_func(voi, 10.0), leq_func(voi, 10.5)) else 0.0
    algebraic[1] = external_variable(voi, states, rates, variables, 1)
    algebraic[2] = constants[2]*(algebraic[1]-computed_constants[0])
    algebraic[5] = external_variable(voi, states, rates, variables, 5)
    algebraic[4] = constants[3]*pow(algebraic[5], 3.0)*states[0]*(algebraic[1]-computed_constants[1])
    algebraic[6] = 0.1*(algebraic[1]+25.0)/(exp((algebraic[1]+25.0)/10.0)-1.0)
    algebraic[7] = 4.0*exp(algebraic[1]/18.0)
    algebraic[3] = constants[4]*pow(states[1], 4.0)*(algebraic[1]-computed_constants[2])
