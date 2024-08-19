# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 1
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 1
ALGEBRAIC_COUNT = 1

VOI_INFO = {"name": "t", "units": "second", "component": "my_model"}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_model"}
]

CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
    {"name": "a", "units": "per_s", "component": "my_model"}
]

ALGEBRAIC_INFO = [
    {"name": "xx", "units": "dimensionless", "component": "my_model"}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def initialise_variables(voi, states, rates, constants, computed_constants, algebraic):
    states[0] = 1.0
    computed_constants[0] = 1.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    rates[0] = computed_constants[0]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[0] = 2.0*states[0]
