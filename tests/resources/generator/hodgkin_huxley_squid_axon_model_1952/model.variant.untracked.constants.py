# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.8.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 4
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 3
ALGEBRAIC_VARIABLE_COUNT = 10

VOI_INFO = {"name": "time", "units": "millisecond", "component": "environment"}

STATE_INFO = [
    {"name": "V", "units": "millivolt", "component": "membrane"},
    {"name": "h", "units": "dimensionless", "component": "sodium_channel_h_gate"},
    {"name": "m", "units": "dimensionless", "component": "sodium_channel_m_gate"},
    {"name": "n", "units": "dimensionless", "component": "potassium_channel_n_gate"}
]

CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
    {"name": "E_L", "units": "millivolt", "component": "leakage_current"},
    {"name": "E_Na", "units": "millivolt", "component": "sodium_channel"},
    {"name": "E_K", "units": "millivolt", "component": "potassium_channel"}
]

ALGEBRAIC_VARIABLE_INFO = [
    {"name": "i_Stim", "units": "microA_per_cm2", "component": "membrane"},
    {"name": "i_L", "units": "microA_per_cm2", "component": "leakage_current"},
    {"name": "i_K", "units": "microA_per_cm2", "component": "potassium_channel"},
    {"name": "i_Na", "units": "microA_per_cm2", "component": "sodium_channel"},
    {"name": "alpha_m", "units": "per_millisecond", "component": "sodium_channel_m_gate"},
    {"name": "beta_m", "units": "per_millisecond", "component": "sodium_channel_m_gate"},
    {"name": "alpha_h", "units": "per_millisecond", "component": "sodium_channel_h_gate"},
    {"name": "beta_h", "units": "per_millisecond", "component": "sodium_channel_h_gate"},
    {"name": "alpha_n", "units": "per_millisecond", "component": "potassium_channel_n_gate"},
    {"name": "beta_n", "units": "per_millisecond", "component": "potassium_channel_n_gate"}
]


def leq_func(x, y):
    return 1.0 if x <= y else 0.0


def geq_func(x, y):
    return 1.0 if x >= y else 0.0


def and_func(x, y):
    return 1.0 if bool(x) & bool(y) else 0.0


def create_states_array():
    return [nan]*STATE_COUNT


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_variables_array():
    return [nan]*ALGEBRAIC_VARIABLE_COUNT


def initialise_arrays(states, rates, constants, computed_constants, algebraic_variables):
    states[0] = 0.0
    states[1] = 0.6
    states[2] = 0.05
    states[3] = 0.325


def compute_computed_constants(voi, states, rates, constants, computed_constants, algebraic_variables):
    membrane_E_R = 0.0
    computed_constants[0] = -10.613+membrane_E_R
    computed_constants[1] = -115.0+membrane_E_R
    computed_constants[2] = 12.0+membrane_E_R


def compute_rates(voi, states, rates, constants, computed_constants, algebraic_variables):
    membrane_Cm = 1.0
    sodium_channel_g_Na = 120.0
    algebraic_variables[3] = states[0]*states[1]*pow(states[2], 3.0)*sodium_channel_g_Na-states[1]*pow(states[2], 3.0)*sodium_channel_g_Na*computed_constants[1]
    algebraic_variables[0] = -20.0 if and_func(geq_func(voi, 10.0), leq_func(voi, 10.5)) else 0.0
    leakage_current_g_L = 0.3
    algebraic_variables[1] = states[0]*leakage_current_g_L-computed_constants[0]*leakage_current_g_L
    potassium_channel_g_K = 36.0
    algebraic_variables[2] = -pow(states[3], 4.0)*computed_constants[2]*potassium_channel_g_K+states[0]*pow(states[3], 4.0)*potassium_channel_g_K
    rates[0] = (-algebraic_variables[2]-algebraic_variables[1]+algebraic_variables[0]-algebraic_variables[3])/membrane_Cm
    algebraic_variables[4] = 0.1*states[0]/(-1.0+exp(2.5+0.1*states[0]))+2.5/(-1.0+exp(2.5+0.1*states[0]))
    algebraic_variables[5] = 4.0*exp(0.0555555555555556*states[0])
    rates[2] = -states[2]*algebraic_variables[5]+(1.0-states[2])*algebraic_variables[4]
    algebraic_variables[6] = 0.07*exp(0.05*states[0])
    algebraic_variables[7] = 1.0/(1.0+exp(3.0+0.1*states[0]))
    rates[1] = -states[1]*algebraic_variables[7]+(1.0-states[1])*algebraic_variables[6]
    algebraic_variables[8] = 0.01*states[0]/(-1.0+exp(1.0+0.1*states[0]))+0.1/(-1.0+exp(1.0+0.1*states[0]))
    algebraic_variables[9] = 0.125*exp(0.0125*states[0])
    rates[3] = -states[3]*algebraic_variables[9]+(1.0-states[3])*algebraic_variables[8]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic_variables):
    leakage_current_g_L = 0.3
    algebraic_variables[1] = states[0]*leakage_current_g_L-computed_constants[0]*leakage_current_g_L
    sodium_channel_g_Na = 120.0
    algebraic_variables[3] = states[0]*states[1]*pow(states[2], 3.0)*sodium_channel_g_Na-states[1]*pow(states[2], 3.0)*sodium_channel_g_Na*computed_constants[1]
    algebraic_variables[4] = 0.1*states[0]/(-1.0+exp(2.5+0.1*states[0]))+2.5/(-1.0+exp(2.5+0.1*states[0]))
    algebraic_variables[5] = 4.0*exp(0.0555555555555556*states[0])
    algebraic_variables[6] = 0.07*exp(0.05*states[0])
    algebraic_variables[7] = 1.0/(1.0+exp(3.0+0.1*states[0]))
    potassium_channel_g_K = 36.0
    algebraic_variables[2] = -pow(states[3], 4.0)*computed_constants[2]*potassium_channel_g_K+states[0]*pow(states[3], 4.0)*potassium_channel_g_K
    algebraic_variables[8] = 0.01*states[0]/(-1.0+exp(1.0+0.1*states[0]))+0.1/(-1.0+exp(1.0+0.1*states[0]))
    algebraic_variables[9] = 0.125*exp(0.0125*states[0])
