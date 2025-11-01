# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.6.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 2
CONSTANT_COUNT = 1
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 0

VOI_INFO = {"name": "t", "units": "second", "component": "environment"}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_first_ode"},
    {"name": "x", "units": "dimensionless", "component": "my_second_ode"}
]

CONSTANT_INFO = [
    {"name": "a", "units": "per_s", "component": "my_second_ode"}
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_INFO = [
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def initialise_variables(states, rates, constants, computed_constants, algebraic):
    states[0] = 1.0
    states[1] = 1.0
    constants[0] = 1.0


def compute_computed_constants(states, rates, constants, computed_constants, algebraic):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    rates[0] = 1.0
    rates[1] = constants[0]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    pass
