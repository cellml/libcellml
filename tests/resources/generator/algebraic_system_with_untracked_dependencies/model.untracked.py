# The content of this file was generated using the Python profile of libCellML 0.7.1.

from enum import Enum
from math import *


__version__ = "0.8.0"
LIBCELLML_VERSION = "0.7.1"

STATE_COUNT = 3
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_VARIABLE_COUNT = 3

VOI_INFO = {"name": "t", "units": "dimensionless", "component": "my_component"}

STATE_INFO = [
    {"name": "z", "units": "dimensionless", "component": "my_component"},
    {"name": "v", "units": "dimensionless", "component": "my_component"},
    {"name": "x", "units": "dimensionless", "component": "my_component"}
]

CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_VARIABLE_INFO = [
    {"name": "y", "units": "dimensionless", "component": "my_component"},
    {"name": "a", "units": "dimensionless", "component": "my_component"},
    {"name": "w", "units": "dimensionless", "component": "my_component"}
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

    algebraic_variables[2] = u[0]
    algebraic_variables[0] = u[1]

    my_component_k = 2.0
    my_component_kc = 2.0*my_component_k
    my_component_kc2 = 3.0*my_component_kc
    my_component_r = 3.0*rates[2]+states[2]
    my_component_q = my_component_r+1.0

    f[0] = algebraic_variables[0]+algebraic_variables[2]-(3.0*states[2]+my_component_kc2)
    f[1] = algebraic_variables[0]-algebraic_variables[2]*exp(algebraic_variables[2])-(my_component_q+states[2])


def find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables):
    u = [nan]*2

    u[0] = algebraic_variables[2]
    u[1] = algebraic_variables[0]

    u = nla_solve(objective_function_0, u, 2, [voi, states, rates, constants, computed_constants, algebraic_variables])

    algebraic_variables[2] = u[0]
    algebraic_variables[0] = u[1]


def initialise_arrays(states, rates, constants, computed_constants, algebraic_variables):
    states[0] = 0.0
    states[1] = 0.0
    states[2] = 1.0
    algebraic_variables[0] = 0.0
    algebraic_variables[2] = 0.0


def compute_computed_constants(voi, states, rates, constants, computed_constants, algebraic_variables):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic_variables):
    rates[2] = -states[2]
    find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables)
    rates[0] = algebraic_variables[0]
    my_component_l = states[2]+1.0
    algebraic_variables[1] = 2.0*my_component_l+algebraic_variables[0]
    rates[1] = algebraic_variables[1]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic_variables):
    find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables)
    my_component_l = states[2]+1.0
    algebraic_variables[1] = 2.0*my_component_l+algebraic_variables[0]
