# The content of this file was generated using the Python profile of libCellML 0.7.1.

from enum import Enum
from math import *


__version__ = "0.8.0"
LIBCELLML_VERSION = "0.7.1"

STATE_COUNT = 2
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_VARIABLE_COUNT = 4

VOI_INFO = {"name": "t", "units": "dimensionless", "component": "main"}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "main"},
    {"name": "y", "units": "dimensionless", "component": "main"}
]

CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_VARIABLE_INFO = [
    {"name": "z", "units": "dimensionless", "component": "main"},
    {"name": "a", "units": "dimensionless", "component": "main"},
    {"name": "b", "units": "dimensionless", "component": "main"},
    {"name": "c", "units": "dimensionless", "component": "main"}
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

    algebraic_variables[1] = u[0]
    algebraic_variables[2] = u[1]
    algebraic_variables[3] = u[2]

    f[0] = sin(algebraic_variables[1])-states[0]
    f[1] = algebraic_variables[1]+pow(algebraic_variables[2], 3.0)-2.0
    f[2] = algebraic_variables[2]*algebraic_variables[3]+pow(algebraic_variables[3], 3.0)-1.0


def find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables):
    u = [nan]*3

    u[0] = algebraic_variables[1]
    u[1] = algebraic_variables[2]
    u[2] = algebraic_variables[3]

    u = nla_solve(objective_function_0, u, 3, [voi, states, rates, constants, computed_constants, algebraic_variables])

    algebraic_variables[1] = u[0]
    algebraic_variables[2] = u[1]
    algebraic_variables[3] = u[2]


def initialise_arrays(states, rates, constants, computed_constants, algebraic_variables):
    states[0] = 0.0
    states[1] = 0.0
    algebraic_variables[1] = 1.0
    algebraic_variables[2] = 1.0
    algebraic_variables[3] = 1.0


def compute_computed_constants(voi, states, rates, constants, computed_constants, algebraic_variables):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic_variables):
    rates[0] = 1.0
    find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables)
    algebraic_variables[0] = algebraic_variables[3]+1.0
    rates[1] = algebraic_variables[0]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic_variables):
    find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables)
    algebraic_variables[0] = algebraic_variables[3]+1.0
