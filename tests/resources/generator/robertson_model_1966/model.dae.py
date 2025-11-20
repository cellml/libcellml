# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.6.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 2
CONSTANT_COUNT = 3
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_VARIABLE_COUNT = 2

VOI_INFO = {"name": "t", "units": "dimensionless", "component": "main"}

STATE_INFO = [
    {"name": "y2", "units": "dimensionless", "component": "main"},
    {"name": "y1", "units": "dimensionless", "component": "main"}
]

CONSTANT_INFO = [
    {"name": "k3", "units": "dimensionless", "component": "main"},
    {"name": "k1", "units": "dimensionless", "component": "main"},
    {"name": "k2", "units": "dimensionless", "component": "main"}
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_INFO = [
    {"name": "y3", "units": "dimensionless", "component": "main"},
    {"name": "y2_scaled", "units": "dimensionless", "component": "main"}
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

    algebraicVariables[0] = u[0]

    f[0] = 1.0-(states[1]+states[0]+algebraicVariables[0])


def find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables):
    u = [nan]*1

    u[0] = algebraicVariables[0]

    u = nla_solve(objective_function_0, u, 1, [voi, states, rates, constants, computed_constants, algebraic_variables])

    algebraicVariables[0] = u[0]


def initialise_arrays(states, rates, constants, computed_constants, algebraic_variables):
    states[0] = 0.0
    states[1] = 1.0
    constants[0] = 1.0e4
    constants[1] = 0.04
    constants[2] = 3.0e7
    algebraicVariables[0] = 0.0


def compute_computed_constants(states, rates, constants, computed_constants, algebraic):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic_variables):
    find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables)
    rates[1] = -constants[1]*states[1]+constants[0]*states[0]*algebraicVariables[0]
    rates[0] = constants[1]*states[1]-constants[2]*pow(states[0], 2.0)-constants[0]*states[0]*algebraicVariables[0]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic_variables):
    find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables)
    algebraicVariables[1] = 10000.0*states[0]
