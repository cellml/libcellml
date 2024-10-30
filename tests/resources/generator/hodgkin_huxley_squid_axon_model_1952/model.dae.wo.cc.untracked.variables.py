# The content of this file was generated using the Python profile of libCellML 0.6.2.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.2"

STATE_COUNT = 4
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 10

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


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


from nlasolver import nla_solve


def objective_function_0(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[0] = u[0]

    f[0] = algebraic[0]-(-20.0 if and_func(geq_func(voi, 10.0), leq_func(voi, 10.5)) else 0.0)-0.0


def find_root_0(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[0]

    u = nla_solve(objective_function_0, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[0] = u[0]


def objective_function_1(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    rates[0] = u[0]

    membrane_Cm = 1.0

    f[0] = rates[0]-(-(-algebraic[0]+algebraic[3]+algebraic[2]+algebraic[1])/membrane_Cm)-0.0


def find_root_1(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = rates[0]

    u = nla_solve(objective_function_1, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    rates[0] = u[0]


def objective_function_2(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[1] = u[0]

    leakage_current_g_L = 0.3
    membrane_E_R = 0.0
    leakage_current_E_L = membrane_E_R-10.613

    f[0] = algebraic[1]-leakage_current_g_L*(states[0]-leakage_current_E_L)-0.0


def find_root_2(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[1]

    u = nla_solve(objective_function_2, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[1] = u[0]


def objective_function_3(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[3] = u[0]

    sodium_channel_g_Na = 120.0
    membrane_E_R = 0.0
    sodium_channel_E_Na = membrane_E_R-115.0

    f[0] = algebraic[3]-sodium_channel_g_Na*pow(states[2], 3.0)*states[1]*(states[0]-sodium_channel_E_Na)-0.0


def find_root_3(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[3]

    u = nla_solve(objective_function_3, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[3] = u[0]


def objective_function_4(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[4] = u[0]

    f[0] = algebraic[4]-0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0)-0.0


def find_root_4(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[4]

    u = nla_solve(objective_function_4, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[4] = u[0]


def objective_function_5(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[5] = u[0]

    f[0] = algebraic[5]-4.0*exp(states[0]/18.0)-0.0


def find_root_5(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[5]

    u = nla_solve(objective_function_5, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[5] = u[0]


def objective_function_6(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    rates[2] = u[0]

    f[0] = rates[2]-(algebraic[4]*(1.0-states[2])-algebraic[5]*states[2])-0.0


def find_root_6(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = rates[2]

    u = nla_solve(objective_function_6, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    rates[2] = u[0]


def objective_function_7(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[6] = u[0]

    f[0] = algebraic[6]-0.07*exp(states[0]/20.0)-0.0


def find_root_7(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[6]

    u = nla_solve(objective_function_7, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[6] = u[0]


def objective_function_8(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[7] = u[0]

    f[0] = algebraic[7]-1.0/(exp((states[0]+30.0)/10.0)+1.0)-0.0


def find_root_8(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[7]

    u = nla_solve(objective_function_8, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[7] = u[0]


def objective_function_9(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    rates[1] = u[0]

    f[0] = rates[1]-(algebraic[6]*(1.0-states[1])-algebraic[7]*states[1])-0.0


def find_root_9(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = rates[1]

    u = nla_solve(objective_function_9, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    rates[1] = u[0]


def objective_function_10(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[2] = u[0]

    potassium_channel_g_K = 36.0
    membrane_E_R = 0.0
    potassium_channel_E_K = membrane_E_R+12.0

    f[0] = algebraic[2]-potassium_channel_g_K*pow(states[3], 4.0)*(states[0]-potassium_channel_E_K)-0.0


def find_root_10(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[2]

    u = nla_solve(objective_function_10, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[2] = u[0]


def objective_function_11(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[8] = u[0]

    f[0] = algebraic[8]-0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0)-0.0


def find_root_11(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[8]

    u = nla_solve(objective_function_11, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[8] = u[0]


def objective_function_12(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[9] = u[0]

    f[0] = algebraic[9]-0.125*exp(states[0]/80.0)-0.0


def find_root_12(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[9]

    u = nla_solve(objective_function_12, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[9] = u[0]


def objective_function_13(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    rates[3] = u[0]

    f[0] = rates[3]-(algebraic[8]*(1.0-states[3])-algebraic[9]*states[3])-0.0


def find_root_13(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = rates[3]

    u = nla_solve(objective_function_13, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

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
    algebraic[0] = 0.0
    algebraic[1] = 0.0
    algebraic[2] = 0.0
    algebraic[3] = 0.0
    algebraic[4] = 0.0
    algebraic[5] = 0.0
    algebraic[6] = 0.0
    algebraic[7] = 0.0
    algebraic[8] = 0.0
    algebraic[9] = 0.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    membrane_Cm = 1.0
    find_root_0(voi, states, rates, constants, computed_constants, algebraic)
    leakage_current_g_L = 0.3
    membrane_E_R = 0.0
    leakage_current_E_L = membrane_E_R-10.613
    find_root_2(voi, states, rates, constants, computed_constants, algebraic)
    potassium_channel_g_K = 36.0
    potassium_channel_E_K = membrane_E_R+12.0
    find_root_11(voi, states, rates, constants, computed_constants, algebraic)
    find_root_12(voi, states, rates, constants, computed_constants, algebraic)
    find_root_13(voi, states, rates, constants, computed_constants, algebraic)
    find_root_10(voi, states, rates, constants, computed_constants, algebraic)
    sodium_channel_g_Na = 120.0
    sodium_channel_E_Na = membrane_E_R-115.0
    find_root_7(voi, states, rates, constants, computed_constants, algebraic)
    find_root_8(voi, states, rates, constants, computed_constants, algebraic)
    find_root_9(voi, states, rates, constants, computed_constants, algebraic)
    find_root_4(voi, states, rates, constants, computed_constants, algebraic)
    find_root_5(voi, states, rates, constants, computed_constants, algebraic)
    find_root_6(voi, states, rates, constants, computed_constants, algebraic)
    find_root_3(voi, states, rates, constants, computed_constants, algebraic)
    find_root_1(voi, states, rates, constants, computed_constants, algebraic)


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    membrane_Cm = 1.0
    find_root_0(voi, states, rates, constants, computed_constants, algebraic)
    leakage_current_g_L = 0.3
    membrane_E_R = 0.0
    leakage_current_E_L = membrane_E_R-10.613
    find_root_2(voi, states, rates, constants, computed_constants, algebraic)
    potassium_channel_g_K = 36.0
    potassium_channel_E_K = membrane_E_R+12.0
    find_root_11(voi, states, rates, constants, computed_constants, algebraic)
    find_root_12(voi, states, rates, constants, computed_constants, algebraic)
    find_root_13(voi, states, rates, constants, computed_constants, algebraic)
    find_root_10(voi, states, rates, constants, computed_constants, algebraic)
    sodium_channel_g_Na = 120.0
    sodium_channel_E_Na = membrane_E_R-115.0
    find_root_7(voi, states, rates, constants, computed_constants, algebraic)
    find_root_8(voi, states, rates, constants, computed_constants, algebraic)
    find_root_9(voi, states, rates, constants, computed_constants, algebraic)
    find_root_4(voi, states, rates, constants, computed_constants, algebraic)
    find_root_5(voi, states, rates, constants, computed_constants, algebraic)
    find_root_6(voi, states, rates, constants, computed_constants, algebraic)
    find_root_3(voi, states, rates, constants, computed_constants, algebraic)
    find_root_1(voi, states, rates, constants, computed_constants, algebraic)
