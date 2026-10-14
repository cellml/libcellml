# The content of this file was generated using the Python profile of libCellML 0.7.1.

from enum import Enum
from math import *


__version__ = "0.8.0"
LIBCELLML_VERSION = "0.7.1"

STATE_COUNT = 1
CONSTANT_COUNT = 1
COMPUTED_CONSTANT_COUNT = 1
ALGEBRAIC_VARIABLE_COUNT = 3

VOI_INFO = {"name": "t", "units": "dimensionless", "component": "main"}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "main"}
]

CONSTANT_INFO = [
    {"name": "k", "units": "dimensionless", "component": "main"}
]

COMPUTED_CONSTANT_INFO = [
    {"name": "cc", "units": "dimensionless", "component": "main"}
]

ALGEBRAIC_VARIABLE_INFO = [
    {"name": "a", "units": "dimensionless", "component": "main"},
    {"name": "b", "units": "dimensionless", "component": "main"},
    {"name": "d", "units": "dimensionless", "component": "main"}
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

    algebraic_variables[0] = u[0]

    f[0] = algebraic_variables[0]*algebraic_variables[0]-(states[0]+3.0)


def find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables):
    u = [nan]*1

    u[0] = algebraic_variables[0]

    u = nla_solve(objective_function_0, u, 1, [voi, states, rates, constants, computed_constants, algebraic_variables])

    algebraic_variables[0] = u[0]


def objective_function_1(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic_variables = data[5]

    algebraic_variables[1] = u[0]

    f[0] = algebraic_variables[1]*algebraic_variables[1]*algebraic_variables[1]-(states[0]+computed_constants[0])


def find_root_1(voi, states, rates, constants, computed_constants, algebraic_variables):
    u = [nan]*1

    u[0] = algebraic_variables[1]

    u = nla_solve(objective_function_1, u, 1, [voi, states, rates, constants, computed_constants, algebraic_variables])

    algebraic_variables[1] = u[0]


def objective_function_2(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic_variables = data[5]

    algebraic_variables[2] = u[0]

    f[0] = sin(algebraic_variables[2])-2.0*states[0]


def find_root_2(voi, states, rates, constants, computed_constants, algebraic_variables):
    u = [nan]*1

    u[0] = algebraic_variables[2]

    u = nla_solve(objective_function_2, u, 1, [voi, states, rates, constants, computed_constants, algebraic_variables])

    algebraic_variables[2] = u[0]


def initialise_arrays(states, rates, constants, computed_constants, algebraic_variables):
    states[0] = 1.0
    constants[0] = 3.0
    algebraic_variables[0] = 1.0
    algebraic_variables[2] = 1.0


def compute_computed_constants(voi, states, rates, constants, computed_constants, algebraic_variables):
    computed_constants[0] = 2.0*constants[0]
    algebraic_variables[1] = computed_constants[0]


def compute_rates(voi, states, rates, constants, computed_constants, algebraic_variables):
    rates[0] = constants[0]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic_variables):
    find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables)
    find_root_1(voi, states, rates, constants, computed_constants, algebraic_variables)
    find_root_2(voi, states, rates, constants, computed_constants, algebraic_variables)
