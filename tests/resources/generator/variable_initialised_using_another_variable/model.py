# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.6.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 22
CONSTANT_COUNT = 2
COMPUTED_CONSTANT_COUNT = 2
ALGEBRAIC_COUNT = 22

VOI_INFO = {"name": "t", "units": "dimensionless", "component": "main"}

STATE_INFO = [
    {"name": "xStateStateCst", "units": "dimensionless", "component": "main"},
    {"name": "kStateStateCst", "units": "dimensionless", "component": "main"},
    {"name": "xStateStateCompCst", "units": "dimensionless", "component": "main"},
    {"name": "kStateStateCompCst", "units": "dimensionless", "component": "main"},
    {"name": "xStateStateState", "units": "dimensionless", "component": "main"},
    {"name": "kStateStateState", "units": "dimensionless", "component": "main"},
    {"name": "xStateStateNla", "units": "dimensionless", "component": "main"},
    {"name": "kStateStateNla", "units": "dimensionless", "component": "main"},
    {"name": "kNlaStateCst", "units": "dimensionless", "component": "main"},
    {"name": "kNlaStateCompCst", "units": "dimensionless", "component": "main"},
    {"name": "kNlaStateState", "units": "dimensionless", "component": "main"},
    {"name": "kNlaStateNla", "units": "dimensionless", "component": "main"},
    {"name": "xStateNlaCst", "units": "dimensionless", "component": "main"},
    {"name": "xStateNlaCompCst", "units": "dimensionless", "component": "main"},
    {"name": "xStateNlaState", "units": "dimensionless", "component": "main"},
    {"name": "xStateNlaNla", "units": "dimensionless", "component": "main"},
    {"name": "xStateCst", "units": "dimensionless", "component": "main"},
    {"name": "xStateCompCst", "units": "dimensionless", "component": "main"},
    {"name": "xStateState", "units": "dimensionless", "component": "main"},
    {"name": "kStateState", "units": "dimensionless", "component": "main"},
    {"name": "xStateNla", "units": "dimensionless", "component": "main"},
    {"name": "kNlaState", "units": "dimensionless", "component": "main"}
]

CONSTANT_INFO = [
    {"name": "kStateCst", "units": "dimensionless", "component": "main"},
    {"name": "kNlaCst", "units": "dimensionless", "component": "main"}
]

COMPUTED_CONSTANT_INFO = [
    {"name": "kStateCompCst", "units": "dimensionless", "component": "main"},
    {"name": "kNlaCompCst", "units": "dimensionless", "component": "main"}
]

ALGEBRAIC_INFO = [
    {"name": "xNlaStateCst", "units": "dimensionless", "component": "main"},
    {"name": "xNlaStateCompCst", "units": "dimensionless", "component": "main"},
    {"name": "xNlaStateState", "units": "dimensionless", "component": "main"},
    {"name": "xNlaStateNla", "units": "dimensionless", "component": "main"},
    {"name": "kStateNlaCst", "units": "dimensionless", "component": "main"},
    {"name": "kStateNlaCompCst", "units": "dimensionless", "component": "main"},
    {"name": "kStateNlaState", "units": "dimensionless", "component": "main"},
    {"name": "kStateNlaNla", "units": "dimensionless", "component": "main"},
    {"name": "xNlaNlaCst", "units": "dimensionless", "component": "main"},
    {"name": "kNlaNlaCst", "units": "dimensionless", "component": "main"},
    {"name": "xNlaNlaCompCst", "units": "dimensionless", "component": "main"},
    {"name": "kNlaNlaCompCst", "units": "dimensionless", "component": "main"},
    {"name": "xNlaNlaState", "units": "dimensionless", "component": "main"},
    {"name": "kNlaNlaState", "units": "dimensionless", "component": "main"},
    {"name": "xNlaNlaNla", "units": "dimensionless", "component": "main"},
    {"name": "kNlaNlaNla", "units": "dimensionless", "component": "main"},
    {"name": "kStateNla", "units": "dimensionless", "component": "main"},
    {"name": "xNlaCst", "units": "dimensionless", "component": "main"},
    {"name": "xNlaCompCst", "units": "dimensionless", "component": "main"},
    {"name": "xNlaState", "units": "dimensionless", "component": "main"},
    {"name": "xNlaNla", "units": "dimensionless", "component": "main"},
    {"name": "kNlaNla", "units": "dimensionless", "component": "main"}
]


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

    f[0] = voi-algebraic[0]


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

    algebraic[1] = u[0]

    f[0] = voi-algebraic[1]


def find_root_1(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[1]

    u = nla_solve(objective_function_1, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[1] = u[0]


def objective_function_2(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[2] = u[0]

    f[0] = voi-algebraic[2]


def find_root_2(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[2]

    u = nla_solve(objective_function_2, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[2] = u[0]


def objective_function_3(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[3] = u[0]

    f[0] = voi-algebraic[3]


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

    f[0] = voi-algebraic[4]


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

    f[0] = voi-algebraic[5]


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

    algebraic[6] = u[0]

    f[0] = voi-algebraic[6]


def find_root_6(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[6]

    u = nla_solve(objective_function_6, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[6] = u[0]


def objective_function_7(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[7] = u[0]

    f[0] = voi-algebraic[7]


def find_root_7(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[7]

    u = nla_solve(objective_function_7, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[7] = u[0]


def objective_function_8(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[8] = u[0]

    f[0] = voi-algebraic[8]


def find_root_8(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[8]

    u = nla_solve(objective_function_8, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[8] = u[0]


def objective_function_9(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[9] = u[0]

    f[0] = voi-algebraic[9]


def find_root_9(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[9]

    u = nla_solve(objective_function_9, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[9] = u[0]


def objective_function_10(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[10] = u[0]

    f[0] = voi-algebraic[10]


def find_root_10(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[10]

    u = nla_solve(objective_function_10, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[10] = u[0]


def objective_function_11(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[11] = u[0]

    f[0] = voi-algebraic[11]


def find_root_11(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[11]

    u = nla_solve(objective_function_11, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[11] = u[0]


def objective_function_12(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[12] = u[0]

    f[0] = voi-algebraic[12]


def find_root_12(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[12]

    u = nla_solve(objective_function_12, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[12] = u[0]


def objective_function_13(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[13] = u[0]

    f[0] = voi-algebraic[13]


def find_root_13(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[13]

    u = nla_solve(objective_function_13, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[13] = u[0]


def objective_function_14(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[14] = u[0]

    f[0] = voi-algebraic[14]


def find_root_14(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[14]

    u = nla_solve(objective_function_14, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[14] = u[0]


def objective_function_15(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[15] = u[0]

    f[0] = voi-algebraic[15]


def find_root_15(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[15]

    u = nla_solve(objective_function_15, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[15] = u[0]


def objective_function_16(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[16] = u[0]

    f[0] = voi-algebraic[16]


def find_root_16(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[16]

    u = nla_solve(objective_function_16, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[16] = u[0]


def objective_function_17(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[17] = u[0]

    f[0] = voi-algebraic[17]


def find_root_17(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[17]

    u = nla_solve(objective_function_17, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[17] = u[0]


def objective_function_18(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[18] = u[0]

    f[0] = voi-algebraic[18]


def find_root_18(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[18]

    u = nla_solve(objective_function_18, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[18] = u[0]


def objective_function_19(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[19] = u[0]

    f[0] = voi-algebraic[19]


def find_root_19(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[19]

    u = nla_solve(objective_function_19, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[19] = u[0]


def objective_function_20(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[20] = u[0]

    f[0] = voi-algebraic[20]


def find_root_20(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[20]

    u = nla_solve(objective_function_20, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[20] = u[0]


def objective_function_21(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[21] = u[0]

    f[0] = voi-algebraic[21]


def find_root_21(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[21]

    u = nla_solve(objective_function_21, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[21] = u[0]


def initialise_variables(states, rates, constants, computed_constants, algebraic):
    constants[0] = 3.0
    states[1] = constants[0]
    states[0] = states[1]
    states[19] = 5.0
    states[5] = states[19]
    states[4] = states[5]
    algebraic[16] = 7.0
    states[7] = algebraic[16]
    states[6] = states[7]
    states[8] = constants[0]
    states[10] = states[19]
    states[11] = algebraic[16]
    constants[1] = 3.0
    algebraic[4] = constants[1]
    states[12] = algebraic[4]
    states[21] = 5.0
    algebraic[6] = states[21]
    states[14] = algebraic[6]
    algebraic[21] = 7.0
    algebraic[7] = algebraic[21]
    states[15] = algebraic[7]
    states[16] = constants[0]
    states[18] = states[19]
    states[20] = algebraic[16]
    algebraic[0] = states[8]
    algebraic[2] = states[10]
    algebraic[3] = states[11]
    algebraic[9] = constants[1]
    algebraic[8] = algebraic[9]
    algebraic[13] = states[21]
    algebraic[12] = algebraic[13]
    algebraic[15] = algebraic[21]
    algebraic[14] = algebraic[15]
    algebraic[17] = constants[1]
    algebraic[19] = states[21]
    algebraic[20] = algebraic[21]


def compute_computed_constants(states, rates, constants, computed_constants, algebraic):
    computed_constants[0] = 1.23*constants[0]
    states[3] = computed_constants[0]
    states[2] = states[3]
    states[9] = computed_constants[0]
    computed_constants[1] = 1.23*constants[1]
    algebraic[5] = computed_constants[1]
    states[13] = algebraic[5]
    states[17] = computed_constants[0]
    algebraic[1] = states[9]
    algebraic[11] = computed_constants[1]
    algebraic[10] = algebraic[11]
    algebraic[18] = computed_constants[1]


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    rates[0] = 1.23
    rates[1] = 1.23
    rates[2] = 1.23
    rates[3] = 1.23
    rates[4] = 1.23
    rates[5] = 1.23
    rates[6] = 1.23
    rates[7] = 1.23
    rates[8] = 1.23
    rates[9] = 1.23
    rates[10] = 1.23
    rates[11] = 1.23
    rates[12] = 1.23
    rates[13] = 1.23
    rates[14] = 1.23
    rates[15] = 1.23
    rates[16] = 1.23
    rates[17] = 1.23
    rates[18] = 1.23
    rates[19] = 1.23
    rates[20] = 1.23
    rates[21] = 1.23


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    find_root_0(voi, states, rates, constants, computed_constants, algebraic)
    find_root_1(voi, states, rates, constants, computed_constants, algebraic)
    find_root_2(voi, states, rates, constants, computed_constants, algebraic)
    find_root_3(voi, states, rates, constants, computed_constants, algebraic)
    find_root_4(voi, states, rates, constants, computed_constants, algebraic)
    find_root_5(voi, states, rates, constants, computed_constants, algebraic)
    find_root_6(voi, states, rates, constants, computed_constants, algebraic)
    find_root_7(voi, states, rates, constants, computed_constants, algebraic)
    find_root_8(voi, states, rates, constants, computed_constants, algebraic)
    find_root_9(voi, states, rates, constants, computed_constants, algebraic)
    find_root_10(voi, states, rates, constants, computed_constants, algebraic)
    find_root_11(voi, states, rates, constants, computed_constants, algebraic)
    find_root_12(voi, states, rates, constants, computed_constants, algebraic)
    find_root_13(voi, states, rates, constants, computed_constants, algebraic)
    find_root_14(voi, states, rates, constants, computed_constants, algebraic)
    find_root_15(voi, states, rates, constants, computed_constants, algebraic)
    find_root_16(voi, states, rates, constants, computed_constants, algebraic)
    find_root_17(voi, states, rates, constants, computed_constants, algebraic)
    find_root_18(voi, states, rates, constants, computed_constants, algebraic)
    find_root_19(voi, states, rates, constants, computed_constants, algebraic)
    find_root_20(voi, states, rates, constants, computed_constants, algebraic)
    find_root_21(voi, states, rates, constants, computed_constants, algebraic)
