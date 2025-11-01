# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 4
CONSTANT_COUNT = 1
COMPUTED_CONSTANT_COUNT = 3
ALGEBRAIC_COUNT = 9
EXTERNAL_COUNT = 1

VOI_INFO = {"name": "time", "units": "millisecond", "component": "environment"}

STATE_INFO = [
    {"name": "V", "units": "millivolt", "component": "membrane"},
    {"name": "h", "units": "dimensionless", "component": "sodium_channel_h_gate"},
    {"name": "m", "units": "dimensionless", "component": "sodium_channel_m_gate"},
    {"name": "n", "units": "dimensionless", "component": "potassium_channel_n_gate"}
]

CONSTANT_INFO = [
    {"name": "Cm", "units": "microF_per_cm2", "component": "membrane"}
]

COMPUTED_CONSTANT_INFO = [
    {"name": "E_L", "units": "millivolt", "component": "leakage_current"},
    {"name": "E_Na", "units": "millivolt", "component": "sodium_channel"},
    {"name": "E_K", "units": "millivolt", "component": "potassium_channel"}
]

ALGEBRAIC_INFO = [
    {"name": "i_Stim", "units": "microA_per_cm2", "component": "membrane"},
    {"name": "i_L", "units": "microA_per_cm2", "component": "leakage_current"},
    {"name": "i_K", "units": "microA_per_cm2", "component": "potassium_channel"},
    {"name": "alpha_m", "units": "per_millisecond", "component": "sodium_channel_m_gate"},
    {"name": "beta_m", "units": "per_millisecond", "component": "sodium_channel_m_gate"},
    {"name": "alpha_h", "units": "per_millisecond", "component": "sodium_channel_h_gate"},
    {"name": "beta_h", "units": "per_millisecond", "component": "sodium_channel_h_gate"},
    {"name": "alpha_n", "units": "per_millisecond", "component": "potassium_channel_n_gate"},
    {"name": "beta_n", "units": "per_millisecond", "component": "potassium_channel_n_gate"}
]

EXTERNAL_INFO = [
    {"name": "i_Na", "units": "microA_per_cm2", "component": "sodium_channel"}
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


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def create_externals_array():
    return [nan]*EXTERNAL_COUNT


def initialise_variables(states, rates, constants, computed_constants, algebraic):
    states[0] = 0.0
    states[1] = 0.6
    states[2] = 0.05
    states[3] = 0.325
    constants[0] = 1.0


def compute_computed_constants(constants, computed_constants):
    membrane_E_R = 0.0
    computed_constants[0] = membrane_E_R-10.613
    computed_constants[1] = membrane_E_R-115.0
    computed_constants[2] = membrane_E_R+12.0


def compute_rates(voi, states, rates, constants, computed_constants, algebraic, externals, external_variable):
    algebraic[0] = -20.0 if and_func(geq_func(voi, 10.0), leq_func(voi, 10.5)) else 0.0
    leakage_current_g_L = 0.3
    algebraic[1] = leakage_current_g_L*(states[0]-computed_constants[0])
    potassium_channel_g_K = 36.0
    algebraic[2] = potassium_channel_g_K*pow(states[3], 4.0)*(states[0]-computed_constants[2])
    algebraic[3] = 0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0)
    externals[0] = external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, 0)
    rates[0] = -(-algebraic[0]+externals[0]+algebraic[2]+algebraic[1])/constants[0]
    algebraic[4] = 4.0*exp(states[0]/18.0)
    rates[2] = algebraic[3]*(1.0-states[2])-algebraic[4]*states[2]
    algebraic[6] = 1.0/(exp((states[0]+30.0)/10.0)+1.0)
    algebraic[5] = 0.07*exp(states[0]/20.0)
    rates[1] = algebraic[5]*(1.0-states[1])-algebraic[6]*states[1]
    algebraic[8] = 0.125*exp(states[0]/80.0)
    algebraic[7] = 0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0)
    rates[3] = algebraic[7]*(1.0-states[3])-algebraic[8]*states[3]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic, externals, external_variable):
    leakage_current_g_L = 0.3
    algebraic[1] = leakage_current_g_L*(states[0]-computed_constants[0])
    algebraic[3] = 0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0)
    externals[0] = external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, 0)
    algebraic[4] = 4.0*exp(states[0]/18.0)
    algebraic[5] = 0.07*exp(states[0]/20.0)
    algebraic[6] = 1.0/(exp((states[0]+30.0)/10.0)+1.0)
    potassium_channel_g_K = 36.0
    algebraic[2] = potassium_channel_g_K*pow(states[3], 4.0)*(states[0]-computed_constants[2])
    algebraic[7] = 0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0)
    algebraic[8] = 0.125*exp(states[0]/80.0)
