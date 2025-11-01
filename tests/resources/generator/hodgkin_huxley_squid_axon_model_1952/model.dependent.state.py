# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 2
CONSTANT_COUNT = 5
COMPUTED_CONSTANT_COUNT = 3
ALGEBRAIC_COUNT = 10
EXTERNAL_COUNT = 2

VOI_INFO = {"name": "time", "units": "millisecond", "component": "environment"}

STATE_INFO = [
    {"name": "h", "units": "dimensionless", "component": "sodium_channel_h_gate"},
    {"name": "n", "units": "dimensionless", "component": "potassium_channel_n_gate"}
]

CONSTANT_INFO = [
    {"name": "Cm", "units": "microF_per_cm2", "component": "membrane"},
    {"name": "E_R", "units": "millivolt", "component": "membrane"},
    {"name": "g_L", "units": "milliS_per_cm2", "component": "leakage_current"},
    {"name": "g_Na", "units": "milliS_per_cm2", "component": "sodium_channel"},
    {"name": "g_K", "units": "milliS_per_cm2", "component": "potassium_channel"}
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
    {"name": "i_Na", "units": "microA_per_cm2", "component": "sodium_channel"},
    {"name": "alpha_m", "units": "per_millisecond", "component": "sodium_channel_m_gate"},
    {"name": "beta_m", "units": "per_millisecond", "component": "sodium_channel_m_gate"},
    {"name": "alpha_h", "units": "per_millisecond", "component": "sodium_channel_h_gate"},
    {"name": "beta_h", "units": "per_millisecond", "component": "sodium_channel_h_gate"},
    {"name": "alpha_n", "units": "per_millisecond", "component": "potassium_channel_n_gate"},
    {"name": "beta_n", "units": "per_millisecond", "component": "potassium_channel_n_gate"}
]

EXTERNAL_INFO = [
    {"name": "V", "units": "millivolt", "component": "membrane"},
    {"name": "m", "units": "dimensionless", "component": "sodium_channel_m_gate"}
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
    states[0] = 0.6
    states[1] = 0.325
    constants[0] = 1.0
    constants[1] = 0.0
    constants[2] = 0.3
    constants[3] = 120.0
    constants[4] = 36.0


def compute_computed_constants(constants, computed_constants):
    computed_constants[0] = constants[1]-10.613
    computed_constants[1] = constants[1]-115.0
    computed_constants[2] = constants[1]+12.0


def compute_rates(voi, states, rates, constants, computed_constants, algebraic, externals, external_variable):
    externals[0] = external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, 0)
    algebraic[7] = 1.0/(exp((externals[0]+30.0)/10.0)+1.0)
    algebraic[6] = 0.07*exp(externals[0]/20.0)
    rates[0] = algebraic[6]*(1.0-states[0])-algebraic[7]*states[0]
    algebraic[9] = 0.125*exp(externals[0]/80.0)
    algebraic[8] = 0.01*(externals[0]+10.0)/(exp((externals[0]+10.0)/10.0)-1.0)
    rates[1] = algebraic[8]*(1.0-states[1])-algebraic[9]*states[1]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic, externals, external_variable):
    algebraic[0] = -20.0 if and_func(geq_func(voi, 10.0), leq_func(voi, 10.5)) else 0.0
    externals[0] = external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, 0)
    algebraic[1] = constants[2]*(externals[0]-computed_constants[0])
    externals[1] = external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, 1)
    algebraic[3] = constants[3]*pow(externals[1], 3.0)*states[0]*(externals[0]-computed_constants[1])
    algebraic[4] = 0.1*(externals[0]+25.0)/(exp((externals[0]+25.0)/10.0)-1.0)
    algebraic[5] = 4.0*exp(externals[0]/18.0)
    algebraic[2] = constants[4]*pow(states[1], 4.0)*(externals[0]-computed_constants[2])
