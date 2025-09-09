# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.6.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 1
CONSTANT_COUNT = 1
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 0

VOI_INFO = {"name": "t", "units": "second", "component": "component_1"}

STATE_INFO = [
    {"name": "X", "units": "dimensionless", "component": "component_1"}
]

CONSTANT_INFO = [
    {"name": "X_init", "units": "dimensionless", "component": "component_2"}
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
    constants[0] = 7.0
    states[0] = constants[0]


def compute_computed_constants(states, rates, constants, computed_constants, algebraic):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    rates[0] = 3.0


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    pass
