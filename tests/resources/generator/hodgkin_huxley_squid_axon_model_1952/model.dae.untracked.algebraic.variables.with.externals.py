# The content of this file was generated using the Python profile of libCellML 0.6.1.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.1"

STATE_COUNT = 3
CONSTANT_COUNT = 5
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 0
EXTERNAL_COUNT = 3

VOI_INFO = {"name": "time", "units": "millisecond", "component": "environment"}

STATE_INFO = [
    {"name": "h", "units": "dimensionless", "component": "sodium_channel_h_gate"},
    {"name": "m", "units": "dimensionless", "component": "sodium_channel_m_gate"},
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
]

ALGEBRAIC_INFO = [
]

EXTERNAL_INFO = [
    {"name": "V", "units": "millivolt", "component": "membrane"},
    {"name": "i_Na", "units": "microA_per_cm2", "component": "sodium_channel"},
    {"name": "alpha_n", "units": "per_millisecond", "component": "potassium_channel_n_gate"}
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

    f[0] = membrane_i_Stim-(-20.0 if and_func(geq_func(voi, 10.0), leq_func(voi, 10.5)) else 0.0)-0.0


def find_root_0(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[0]

    u = nla_solve(objective_function_0, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[0] = u[0]


def objective_function_2(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[3] = u[0]

    f[0] = leakage_current_E_L-(constants[1]-10.613)-0.0


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

    f[0] = leakage_current_i_L-constants[2]*(externals[0]-leakage_current_E_L)-0.0


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

    f[0] = sodium_channel_E_Na-(constants[1]-115.0)-0.0


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

    algebraic[5] = u[0]

    f[0] = sodium_channel_m_gate_alpha_m-0.1*(externals[0]+25.0)/(exp((externals[0]+25.0)/10.0)-1.0)-0.0


def find_root_6(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[5]

    u = nla_solve(objective_function_6, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[5] = u[0]


def objective_function_7(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[6] = u[0]

    f[0] = sodium_channel_m_gate_beta_m-4.0*exp(externals[0]/18.0)-0.0


def find_root_7(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[6]

    u = nla_solve(objective_function_7, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[6] = u[0]


def objective_function_8(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    rates[1] = u[0]

    f[0] = rates[1]-(sodium_channel_m_gate_alpha_m*(1.0-states[1])-sodium_channel_m_gate_beta_m*states[1])-0.0


def find_root_8(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = rates[1]

    u = nla_solve(objective_function_8, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    rates[1] = u[0]


def objective_function_9(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[7] = u[0]

    f[0] = sodium_channel_h_gate_alpha_h-0.07*exp(externals[0]/20.0)-0.0


def find_root_9(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[7]

    u = nla_solve(objective_function_9, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[7] = u[0]


def objective_function_10(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[8] = u[0]

    f[0] = sodium_channel_h_gate_beta_h-1.0/(exp((externals[0]+30.0)/10.0)+1.0)-0.0


def find_root_10(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[8]

    u = nla_solve(objective_function_10, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[8] = u[0]


def objective_function_11(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    rates[0] = u[0]

    f[0] = rates[0]-(sodium_channel_h_gate_alpha_h*(1.0-states[0])-sodium_channel_h_gate_beta_h*states[0])-0.0


def find_root_11(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = rates[0]

    u = nla_solve(objective_function_11, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    rates[0] = u[0]


def objective_function_12(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[9] = u[0]

    f[0] = potassium_channel_E_K-(constants[1]+12.0)-0.0


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

    algebraic[2] = u[0]

    f[0] = potassium_channel_i_K-constants[4]*pow(states[2], 4.0)*(externals[0]-potassium_channel_E_K)-0.0


def find_root_13(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[2]

    u = nla_solve(objective_function_13, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[2] = u[0]


def objective_function_15(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    algebraic[10] = u[0]

    f[0] = potassium_channel_n_gate_beta_n-0.125*exp(externals[0]/80.0)-0.0


def find_root_15(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[10]

    u = nla_solve(objective_function_15, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    algebraic[10] = u[0]


def objective_function_16(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]
    externals = data[6]

    rates[2] = u[0]

    f[0] = rates[2]-(externals[2]*(1.0-states[2])-potassium_channel_n_gate_beta_n*states[2])-0.0


def find_root_16(voi, states, rates, constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = rates[2]

    u = nla_solve(objective_function_16, u, 1, [voi, states, rates, constants, computed_constants, algebraic, externals])

    rates[2] = u[0]


def initialise_variables(states, rates, constants, computed_constants, algebraic):
    states[0] = 0.6
    states[1] = 0.05
    states[2] = 0.325
    rates[0] = 0.0
    rates[1] = 0.0
    rates[2] = 0.0
    constants[0] = 1.0
    constants[1] = 0.0
    constants[2] = 0.3
    constants[3] = 120.0
    constants[4] = 36.0
    membrane_i_Stim = 0.0
    leakage_current_i_L = 0.0
    potassium_channel_i_K = 0.0
    leakage_current_E_L = 0.0
    sodium_channel_E_Na = 0.0
    sodium_channel_m_gate_alpha_m = 0.0
    sodium_channel_m_gate_beta_m = 0.0
    sodium_channel_h_gate_alpha_h = 0.0
    sodium_channel_h_gate_beta_h = 0.0
    potassium_channel_E_K = 0.0
    potassium_channel_n_gate_beta_n = 0.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic, externals, external_variable):
    externals[0] = external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, 0)
    find_root_6(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_7(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_8(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_9(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_10(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_11(voi, states, rates, constants, computed_constants, algebraic, externals)
    externals[2] = external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, 2)
    find_root_15(voi, states, rates, constants, computed_constants, algebraic, externals)
    find_root_16(voi, states, rates, constants, computed_constants, algebraic, externals)


def compute_variables(voi, states, rates, constants, computed_constants, algebraic, externals, external_variable):
    externals[0] = external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, 0)
    externals[2] = external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, 2)
    externals[1] = external_variable(voi, states, rates, constants, computed_constants, algebraic, externals, 1)
