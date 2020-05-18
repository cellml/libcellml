# The content of this file was generated using the Python profile of libCellML 0.2.0.

from enum import Enum
from math import *


__version__ = "0.1.0"
LIBCELLML_VERSION = "0.2.0"

STATE_COUNT = 4
VARIABLE_COUNT = 18


class VariableType(Enum):
    CONSTANT = 1
    COMPUTED_CONSTANT = 2
    ALGEBRAIC = 3


VOI_INFO = {"name": "t", "units": "ms", "component": "membrane"}

STATE_INFO = [
    {"name": "m", "units": "dimensionless", "component": "mGate"},
    {"name": "h", "units": "dimensionless", "component": "hGate"},
    {"name": "n", "units": "dimensionless", "component": "nGate"},
    {"name": "V", "units": "mV", "component": "membrane"}
]

VARIABLE_INFO = [
    {"name": "Cm", "units": "microF_per_cm2", "component": "parameters", "type": VariableType.CONSTANT},
    {"name": "E_K", "units": "mV", "component": "parameters", "type": VariableType.CONSTANT},
    {"name": "E_L", "units": "mV", "component": "parameters", "type": VariableType.CONSTANT},
    {"name": "E_Na", "units": "mV", "component": "parameters", "type": VariableType.CONSTANT},
    {"name": "g_K", "units": "mS_per_cm2", "component": "parameters", "type": VariableType.CONSTANT},
    {"name": "g_L", "units": "mS_per_cm2", "component": "parameters", "type": VariableType.CONSTANT},
    {"name": "g_Na", "units": "mS_per_cm2", "component": "parameters", "type": VariableType.CONSTANT},
    {"name": "i_stim", "units": "microA_per_cm2", "component": "membrane", "type": VariableType.ALGEBRAIC},
    {"name": "Na_conductance", "units": "mS_per_cm2", "component": "sodium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "i_Na", "units": "microA_per_cm2", "component": "sodium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_m", "units": "per_ms", "component": "mGate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_m", "units": "per_ms", "component": "mGate", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_h", "units": "per_ms", "component": "hGate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_h", "units": "per_ms", "component": "hGate", "type": VariableType.ALGEBRAIC},
    {"name": "i_K", "units": "microA_per_cm2", "component": "potassium_channel", "type": VariableType.ALGEBRAIC},
    {"name": "alpha_n", "units": "per_millisecond", "component": "nGate", "type": VariableType.ALGEBRAIC},
    {"name": "beta_n", "units": "per_millisecond", "component": "nGate", "type": VariableType.ALGEBRAIC},
    {"name": "i_L", "units": "microA_per_cm2", "component": "leakage", "type": VariableType.ALGEBRAIC}
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


def initialize_states_and_constants(states, variables):
    states[0] = 0.05
    states[1] = 0.6
    states[2] = 0.325
    states[3] = -75.0
    variables[0] = 1.0
    variables[1] = -87.0
    variables[2] = -64.387
    variables[3] = 40.0
    variables[4] = 36.0
    variables[5] = 0.3
    variables[6] = 120.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    variables[10] = -0.1*(states[3]+50.0)/(exp(-(states[3]+50.0)/10.0)-1.0)
    variables[11] = 4.0*exp(-(states[3]+75.0)/18.0)
    rates[0] = variables[10]*(1.0-states[0])-variables[11]*states[0]
    variables[12] = 0.07*exp(-(states[3]+75.0)/20.0)
    variables[13] = 1.0/(exp(-(states[3]+45.0)/10.0)+1.0)
    rates[1] = variables[12]*(1.0-states[1])-variables[13]*states[1]
    variables[15] = -0.01*(states[3]+65.0)/(exp(-(states[3]+65.0)/10.0)-1.0)
    variables[16] = 0.125*exp((states[3]+75.0)/80.0)
    rates[2] = variables[15]*(1.0-states[2])-variables[16]*states[2]
    variables[7] = 20.0 if and_func(geq_func(voi, 10.0), leq_func(voi, 10.5)) else 0.0
    variables[17] = variables[5]*(states[3]-variables[2])
    variables[14] = pow(states[2], 4.0)*variables[4]*(states[3]-variables[1])
    variables[8] = variables[6]*states[1]*pow(states[0], 3.0)
    variables[9] = variables[8]*(states[3]-variables[3])
    rates[3] = -(-variables[7]+variables[9]+variables[14]+variables[17])/variables[0]


def compute_variables(voi, states, rates, variables):
    variables[8] = variables[6]*states[1]*pow(states[0], 3.0)
    variables[9] = variables[8]*(states[3]-variables[3])
    variables[10] = -0.1*(states[3]+50.0)/(exp(-(states[3]+50.0)/10.0)-1.0)
    variables[11] = 4.0*exp(-(states[3]+75.0)/18.0)
    variables[12] = 0.07*exp(-(states[3]+75.0)/20.0)
    variables[13] = 1.0/(exp(-(states[3]+45.0)/10.0)+1.0)
    variables[14] = pow(states[2], 4.0)*variables[4]*(states[3]-variables[1])
    variables[15] = -0.01*(states[3]+65.0)/(exp(-(states[3]+65.0)/10.0)-1.0)
    variables[16] = 0.125*exp((states[3]+75.0)/80.0)
    variables[17] = variables[5]*(states[3]-variables[2])
