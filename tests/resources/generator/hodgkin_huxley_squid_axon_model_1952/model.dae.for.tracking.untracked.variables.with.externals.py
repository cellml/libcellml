# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 4
CONSTANT_COUNT = 1
COMPUTED_CONSTANT_COUNT = 1
ALGEBRAIC_COUNT = 11
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
    {"name": "E_K", "units": "millivolt", "component": "potassium_channel"}
]

ALGEBRAIC_INFO = [
    {"name": "i_Stim", "units": "microA_per_cm2", "component": "membrane"},
    {"name": "i_L", "units": "microA_per_cm2", "component": "leakage_current"},
    {"name": "i_K", "units": "microA_per_cm2", "component": "potassium_channel"},
    {"name": "E_L", "units": "millivolt", "component": "leakage_current"},
    {"name": "E_Na", "units": "millivolt", "component": "sodium_channel"},
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


from nlasolver import nla_solve


def objective_function_0(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[0] = u[0]

    f[0] = algebraic[0]-(-20.0 if and_func(geq_func(voi, 10.0), leq_func(voi, 10.5)) else 0.0)-0.0


def find_root_0(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[0]

    u = nla_solve(objective_function_0, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[0] = u[0]


def objective_function_1(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    rates[0] = u[0]

    f[0] = rates[0]-(-(-algebraic[0]+externals[0]+algebraic[2]+algebraic[1])/constants[0])-0.0


def find_root_1(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = rates[0]

    u = nla_solve(objective_function_1, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    rates[0] = u[0]


def objective_function_2(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[3] = u[0]

    membrane_E_R = 0.0

    f[0] = algebraic[3]-(membrane_E_R-10.613)-0.0


def find_root_2(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[3]

    u = nla_solve(objective_function_2, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[3] = u[0]


def objective_function_3(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[1] = u[0]

    leakage_current_g_L = 0.3

    f[0] = algebraic[1]-leakage_current_g_L*(states[0]-algebraic[3])-0.0


def find_root_3(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[1]

    u = nla_solve(objective_function_3, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[1] = u[0]


def objective_function_4(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[4] = u[0]

    membrane_E_R = 0.0

    f[0] = algebraic[4]-(membrane_E_R-115.0)-0.0


def find_root_4(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[4]

    u = nla_solve(objective_function_4, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[4] = u[0]


def objective_function_6(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[6] = u[0]

    f[0] = algebraic[6]-4.0*exp(states[0]/18.0)-0.0


def find_root_6(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[6]

    u = nla_solve(objective_function_6, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[6] = u[0]


def objective_function_7(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    rates[2] = u[0]

    f[0] = rates[2]-(algebraic[5]*(1.0-states[2])-algebraic[6]*states[2])-0.0


def find_root_7(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = rates[2]

    u = nla_solve(objective_function_7, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    rates[2] = u[0]


def objective_function_8(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[7] = u[0]

    f[0] = algebraic[7]-0.07*exp(states[0]/20.0)-0.0


def find_root_8(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[7]

    u = nla_solve(objective_function_8, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[7] = u[0]


def objective_function_9(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[8] = u[0]

    f[0] = algebraic[8]-1.0/(exp((states[0]+30.0)/10.0)+1.0)-0.0


def find_root_9(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[8]

    u = nla_solve(objective_function_9, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[8] = u[0]


def objective_function_10(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    rates[1] = u[0]

    f[0] = rates[1]-(algebraic[7]*(1.0-states[1])-algebraic[8]*states[1])-0.0


def find_root_10(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = rates[1]

    u = nla_solve(objective_function_10, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    rates[1] = u[0]


def objective_function_11(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[2] = u[0]

    potassium_channel_g_K = 36.0

    f[0] = algebraic[2]-potassium_channel_g_K*pow(states[3], 4.0)*(states[0]-computed_constants[0])-0.0


def find_root_11(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[2]

    u = nla_solve(objective_function_11, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[2] = u[0]


def objective_function_12(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[9] = u[0]

    f[0] = algebraic[9]-0.01*(states[0]+10.0)/(exp((states[0]+10.0)/10.0)-1.0)-0.0


def find_root_12(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[9]

    u = nla_solve(objective_function_12, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[9] = u[0]


def objective_function_13(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[10] = u[0]

    f[0] = algebraic[10]-0.125*exp(states[0]/80.0)-0.0


def find_root_13(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[10]

    u = nla_solve(objective_function_13, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[10] = u[0]


def objective_function_14(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    rates[3] = u[0]

    f[0] = rates[3]-(algebraic[9]*(1.0-states[3])-algebraic[10]*states[3])-0.0


def find_root_14(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = rates[3]

    u = nla_solve(objective_function_14, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

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
    constants[0] = 1.0
    algebraic[0] = 0.0
    algebraic[1] = 0.0
    algebraic[2] = 0.0
    algebraic[3] = 0.0
    algebraic[4] = 0.0
    algebraic[6] = 0.0
    algebraic[7] = 0.0
    algebraic[8] = 0.0
    algebraic[9] = 0.0
    algebraic[10] = 0.0


def compute_computed_constants(constants, computed_constants):
    membrane_E_R = 0.0
    computed_constants[0] = membrane_E_R+12.0


def compute_rates(voi, states, rates, constants, computed_constants, algebraic, externals, external_variable):
    find_root_0(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_2(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_3(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_13(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_12(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_14(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_11(voi, states, rates, constants, computed_constants, algebraic, externals)
    algebraic[5] = 0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0)
    externals[0] = external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, 0)
    find_root_1(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_6(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_7(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_9(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_8(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_10(voi, states, rates, constants, computed_constants, algebraic, externals)


def compute_variables(voi, states, rates, constants, computed_constants, algebraic, externals, external_variable):
    find_root_3(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_13(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_12(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_14(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_11(voi, states, rates, constants, computed_constants, algebraic, externals)
    algebraic[5] = 0.1*(states[0]+25.0)/(exp((states[0]+25.0)/10.0)-1.0)
    externals[0] = external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, 0)
    find_root_1(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_4(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_6(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_7(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_8(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_9(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_10(voi, states, rates, constants, computed_constants, algebraic, externals)
