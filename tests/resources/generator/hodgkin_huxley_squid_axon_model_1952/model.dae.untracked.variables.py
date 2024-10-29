# The content of this file was generated using the Python profile of libCellML 0.6.2.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.2"

STATE_COUNT = 4
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 0

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
]

ALGEBRAIC_INFO = [
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


from nlasolver import nla_solve


def objective_function_1(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    rates[0] = u[0]

    membrane_Cm = 1.0

    f[0] = rates[0]-(-(-membrane_i_Stim+sodium_channel_i_Na+potassium_channel_i_K+leakage_current_i_L)/membrane_Cm)-0.0


def find_root_1(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = rates[0]

    u = nla_solve(objective_function_1, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    rates[0] = u[0]


def objective_function_8(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    rates[2] = u[0]

    f[0] = rates[2]-(sodium_channel_m_gate_alpha_m*(1.0-states[2])-sodium_channel_m_gate_beta_m*states[2])-0.0


def find_root_8(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = rates[2]

    u = nla_solve(objective_function_8, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    rates[2] = u[0]


def objective_function_11(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    rates[1] = u[0]

    f[0] = rates[1]-(sodium_channel_h_gate_alpha_h*(1.0-states[1])-sodium_channel_h_gate_beta_h*states[1])-0.0


def find_root_11(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = rates[1]

    u = nla_solve(objective_function_11, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    rates[1] = u[0]


def objective_function_16(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    rates[3] = u[0]

    f[0] = rates[3]-(potassium_channel_n_gate_alpha_n*(1.0-states[3])-potassium_channel_n_gate_beta_n*states[3])-0.0


def find_root_16(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = rates[3]

    u = nla_solve(objective_function_16, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    rates[3] = u[0]


def initialise_variables(states, rates, constants, computed_constants, algebraic):
    states[0] = 0.0
    states[1] = 0.6
    states[2] = 0.05
    states[3] = 0.325
    rates[0] = 0.0
    rates[1] = 0.0
    rates[2] = 0.0
    rates[3] = 0.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    membrane_Cm = 1.0
    leakage_current_g_L = 0.3
    membrane_E_R = 0.0
    potassium_channel_g_K = 36.0
    find_root_16(voi, states, rates, constants, computed_constants, algebraic)
    sodium_channel_g_Na = 120.0
    find_root_11(voi, states, rates, constants, computed_constants, algebraic)
    find_root_8(voi, states, rates, constants, computed_constants, algebraic)
    find_root_1(voi, states, rates, constants, computed_constants, algebraic)


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    membrane_Cm = 1.0
    leakage_current_g_L = 0.3
    membrane_E_R = 0.0
    potassium_channel_g_K = 36.0
    find_root_16(voi, states, rates, constants, computed_constants, algebraic)
    sodium_channel_g_Na = 120.0
    find_root_11(voi, states, rates, constants, computed_constants, algebraic)
    find_root_8(voi, states, rates, constants, computed_constants, algebraic)
    find_root_1(voi, states, rates, constants, computed_constants, algebraic)
