# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.7.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 2
CONSTANT_COUNT = 4
COMPUTED_CONSTANT_COUNT = 1
ALGEBRAIC_VARIABLE_COUNT = 14

VOI_INFO = {"name": "t", "units": "second", "component": "main"}

STATE_INFO = [
    {"name": "q_2", "units": "coulomb", "component": "main"},
    {"name": "x", "units": "dimensionless", "component": "main"}
]

CONSTANT_INFO = [
    {"name": "C_q_2", "units": "coulomb_squared_per_joule", "component": "main"},
    {"name": "R_R_1", "units": "joule_second_per_coulomb_squared", "component": "main"},
    {"name": "R_R_3", "units": "joule_second_per_coulomb_squared", "component": "main"},
    {"name": "u_S_u", "units": "joule_per_coulomb", "component": "main"}
]

COMPUTED_CONSTANT_INFO = [
    {"name": "u_0", "units": "joule_per_coulomb", "component": "main"}
]

ALGEBRAIC_VARIABLE_INFO = [
    {"name": "v_q_2", "units": "coulomb_per_second", "component": "main"},
    {"name": "u_q_2", "units": "joule_per_coulomb", "component": "main"},
    {"name": "u_R_1", "units": "joule_per_coulomb", "component": "main"},
    {"name": "v_R_1", "units": "coulomb_per_second", "component": "main"},
    {"name": "u_R_3", "units": "joule_per_coulomb", "component": "main"},
    {"name": "v_R_3", "units": "coulomb_per_second", "component": "main"},
    {"name": "v_0", "units": "coulomb_per_second", "component": "main"},
    {"name": "v_S_u", "units": "coulomb_per_second", "component": "main"},
    {"name": "u_2", "units": "joule_per_coulomb", "component": "main"},
    {"name": "u_3", "units": "joule_per_coulomb", "component": "main"},
    {"name": "v_1", "units": "coulomb_per_second", "component": "main"},
    {"name": "time", "units": "second", "component": "main"},
    {"name": "v_2", "units": "coulomb_per_second", "component": "main"},
    {"name": "v_3", "units": "coulomb_per_second", "component": "main"}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_variables_array():
    return [nan]*ALGEBRAIC_VARIABLE_COUNT


from nlasolver import nla_solve


def objective_function_0(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic_variables = data[5]

    algebraicVariables[2] = u[0]
    algebraicVariables[3] = u[1]
    algebraicVariables[10] = u[2]
    algebraicVariables[13] = u[3]
    algebraicVariables[5] = u[4]
    algebraicVariables[12] = u[5]
    algebraicVariables[0] = u[6]
    algebraicVariables[4] = u[7]
    algebraicVariables[8] = u[8]
    algebraicVariables[6] = u[9]
    algebraicVariables[7] = u[10]

    f[0] = algebraicVariables[3]-algebraicVariables[2]/constants[1]
    f[1] = algebraicVariables[5]-algebraicVariables[4]/constants[2]
    f[2] = algebraicVariables[7]-(-algebraicVariables[6])
    f[3] = algebraicVariables[2]-(computed_constants[0]-algebraicVariables[8])
    f[4] = algebraicVariables[4]-(algebraicVariables[8]-algebraicVariables[9])
    f[5] = algebraicVariables[10]-algebraicVariables[3]/states[1]
    f[6] = algebraicVariables[10]-algebraicVariables[6]
    f[7] = algebraicVariables[12]-algebraicVariables[0]*voi/algebraicVariables[11]
    f[8] = algebraicVariables[12]-algebraicVariables[13]
    f[9] = algebraicVariables[13]-algebraicVariables[5]
    f[10] = algebraicVariables[13]-algebraicVariables[10]


def find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables):
    u = [nan]*11

    u[0] = algebraicVariables[2]
    u[1] = algebraicVariables[3]
    u[2] = algebraicVariables[10]
    u[3] = algebraicVariables[13]
    u[4] = algebraicVariables[5]
    u[5] = algebraicVariables[12]
    u[6] = algebraicVariables[0]
    u[7] = algebraicVariables[4]
    u[8] = algebraicVariables[8]
    u[9] = algebraicVariables[6]
    u[10] = algebraicVariables[7]

    u = nla_solve(objective_function_0, u, 11, [voi, states, rates, constants, computed_constants, algebraic_variables])

    algebraicVariables[2] = u[0]
    algebraicVariables[3] = u[1]
    algebraicVariables[10] = u[2]
    algebraicVariables[13] = u[3]
    algebraicVariables[5] = u[4]
    algebraicVariables[12] = u[5]
    algebraicVariables[0] = u[6]
    algebraicVariables[4] = u[7]
    algebraicVariables[8] = u[8]
    algebraicVariables[6] = u[9]
    algebraicVariables[7] = u[10]


def initialise_arrays(states, rates, constants, computed_constants, algebraic_variables):
    states[0] = 0.0
    states[1] = 0.0
    constants[0] = 4.0
    constants[1] = 4.0
    constants[2] = 4.0
    constants[3] = 12.0
    algebraicVariables[0] = 0.0
    algebraicVariables[2] = 0.0
    algebraicVariables[3] = 0.0
    algebraicVariables[4] = 0.0
    algebraicVariables[5] = 0.0
    algebraicVariables[6] = 0.0
    algebraicVariables[7] = 0.0
    algebraicVariables[8] = 0.0
    algebraicVariables[10] = 0.0
    algebraicVariables[12] = 0.0
    algebraicVariables[13] = 0.0


def compute_computed_constants(voi, states, rates, constants, computed_constants, algebraic_variables):
    computed_constants[0] = constants[3]


def compute_rates(voi, states, rates, constants, computed_constants, algebraic_variables):
    algebraicVariables[1] = states[0]/constants[0]
    algebraicVariables[9] = algebraicVariables[1]
    algebraicVariables[11] = voi
    find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables)
    rates[0] = algebraicVariables[0]
    rates[1] = 1.0/1.0


def compute_variables(voi, states, rates, constants, computed_constants, algebraic_variables):
    algebraicVariables[1] = states[0]/constants[0]
    algebraicVariables[9] = algebraicVariables[1]
    algebraicVariables[11] = voi
    find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables)
