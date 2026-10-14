# The content of this file was generated using the Python profile of libCellML 0.7.1.

from enum import Enum
from math import *


__version__ = "0.8.0"
LIBCELLML_VERSION = "0.7.1"

STATE_COUNT = 3
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_VARIABLE_COUNT = 1

VOI_INFO = {"name": "t", "units": "dimensionless", "component": "main"}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "main"},
    {"name": "y", "units": "dimensionless", "component": "main"},
    {"name": "z", "units": "dimensionless", "component": "main"}
]

CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_VARIABLE_INFO = [
    {"name": "a", "units": "dimensionless", "component": "main"}
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

    main_q = 3.0
    main_k = main_q

    f[0] = algebraic_variables[0]+sin(algebraic_variables[0])-(main_q+main_k)


def find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables):
    u = [nan]*1

    u[0] = algebraic_variables[0]

    u = nla_solve(objective_function_0, u, 1, [voi, states, rates, constants, computed_constants, algebraic_variables])

    algebraic_variables[0] = u[0]


def initialise_arrays(states, rates, constants, computed_constants, algebraic_variables):
    main_q = 3.0
    main_k = main_q
    states[0] = main_k
    states[1] = main_k
    algebraic_variables[0] = 0.0


def compute_computed_constants(voi, states, rates, constants, computed_constants, algebraic_variables):
    main_q = 3.0
    main_k = main_q
    main_cc = 2.0*main_k
    states[2] = main_cc


def compute_rates(voi, states, rates, constants, computed_constants, algebraic_variables):
    main_q = 3.0
    main_k = main_q
    rates[0] = main_q+main_k
    main_cc = 2.0*main_k
    main_kc = main_cc
    rates[1] = main_cc+main_kc
    find_root_0(voi, states, rates, constants, computed_constants, algebraic_variables)
    rates[2] = algebraic_variables[0]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic_variables):
    pass
