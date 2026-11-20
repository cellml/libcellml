# The content of this file was generated using the Python profile of libCellML 0.7.1.

from enum import Enum
from math import *


__version__ = "0.8.0"
LIBCELLML_VERSION = "0.7.1"

STATE_COUNT = 2
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_VARIABLE_COUNT = 1
EXTERNAL_VARIABLE_COUNT = 1

VOI_INFO = {"name": "t", "units": "dimensionless", "component": "environment"}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_ode"},
    {"name": "z", "units": "dimensionless", "component": "my_ode"}
]

CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_VARIABLE_INFO = [
    {"name": "y", "units": "dimensionless", "component": "my_ode"}
]

EXTERNAL_VARIABLE_INFO = [
    {"name": "xx", "units": "dimensionless", "component": "my_algebraic_eqn"}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_variables_array():
    return [nan]*ALGEBRAIC_VARIABLE_COUNT


def create_external_variables_array():
    return [nan]*EXTERNAL_VARIABLE_COUNT


def initialise_arrays(states, rates, constants, computed_constants, algebraic_variables):
    states[0] = 1.0
    states[1] = 0.0


def compute_computed_constants(voi, states, rates, constants, computed_constants, algebraic_variables):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic_variables, external_variables, external_variable):
    rates[0] = 1.0
    external_variables[0] = external_variable(voi, states, rates, constants, computed_constants, algebraic_variables, external_variables, 0)
    algebraic_variables[0] = external_variables[0]+1.0
    rates[1] = algebraic_variables[0]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic_variables, external_variables, external_variable):
    external_variables[0] = external_variable(voi, states, rates, constants, computed_constants, algebraic_variables, external_variables, 0)
    algebraic_variables[0] = external_variables[0]+1.0
