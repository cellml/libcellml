# The content of this file was generated using the Python profile of libCellML 0.7.0.

from enum import Enum
from math import *


__version__ = "0.8.0"
LIBCELLML_VERSION = "0.7.0"

STATE_COUNT = 2
CONSTANT_COUNT = 4
COMPUTED_CONSTANT_COUNT = 1
ALGEBRAIC_VARIABLE_COUNT = 16

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
    {"name": "v_3", "units": "coulomb_per_second", "component": "main"},
    {"name": "z_1", "units": "dimensionless", "component": "main"},
    {"name": "z_0", "units": "dimensionless", "component": "main"}
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

    algebraic_variables[14] = u[0]

    f[0] = algebraic_variables[14]-(-1.0+pow(algebraic_variables[14], 2.0))


def find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables):
    u = [nan]*1

    u[0] = algebraic_variables[14]

    u = nla_solve(objective_function_0, u, 1, [voi, states, rates, constants, computed_constants, algebraic_variables])

    algebraic_variables[14] = u[0]


def initialise_arrays(states, rates, constants, computed_constants, algebraic_variables):
    states[0] = 0.0
    states[1] = 0.0
    constants[0] = 4.0
    constants[1] = 4.0
    constants[2] = 4.0
    constants[3] = 12.0
    algebraic_variables[14] = 0.0


def compute_computed_constants(voi, states, rates, constants, computed_constants, algebraic_variables):
    computed_constants[0] = constants[3]


def compute_rates(voi, states, rates, constants, computed_constants, algebraic_variables):
    algebraic_variables[11] = voi
    algebraic_variables[1] = states[0]/constants[0]
    algebraic_variables[9] = algebraic_variables[1]
    algebraic_variables[2] = -states[1]*computed_constants[0]*constants[1]/(-constants[2]-states[1]*constants[1])+states[1]*algebraic_variables[9]*constants[1]/(-constants[2]-states[1]*constants[1])
    algebraic_variables[3] = algebraic_variables[2]/constants[1]
    algebraic_variables[10] = algebraic_variables[3]/states[1]
    algebraic_variables[13] = algebraic_variables[10]
    algebraic_variables[12] = algebraic_variables[13]
    algebraic_variables[0] = algebraic_variables[12]*algebraic_variables[11]/voi
    rates[0] = algebraic_variables[0]
    rates[1] = 1.0


def compute_variables(voi, states, rates, constants, computed_constants, algebraic_variables):
    algebraic_variables[1] = states[0]/constants[0]
    algebraic_variables[9] = algebraic_variables[1]
    algebraic_variables[2] = -states[1]*computed_constants[0]*constants[1]/(-constants[2]-states[1]*constants[1])+states[1]*algebraic_variables[9]*constants[1]/(-constants[2]-states[1]*constants[1])
    algebraic_variables[3] = algebraic_variables[2]/constants[1]
    algebraic_variables[8] = -algebraic_variables[2]+computed_constants[0]
    algebraic_variables[4] = algebraic_variables[8]-algebraic_variables[9]
    algebraic_variables[5] = algebraic_variables[4]/constants[2]
    algebraic_variables[10] = algebraic_variables[3]/states[1]
    algebraic_variables[6] = algebraic_variables[10]
    algebraic_variables[7] = -algebraic_variables[6]
    algebraic_variables[13] = algebraic_variables[10]
    algebraic_variables[12] = algebraic_variables[13]
    algebraic_variables[0] = algebraic_variables[12]*algebraic_variables[11]/voi
    find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables)
    algebraic_variables[15] = pow(algebraic_variables[14], 2.0)
