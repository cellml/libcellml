# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.6.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 3
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 0

VOI_INFO = {"name": "t", "units": "second", "component": "environment"}

STATE_INFO = [
    {"name": "x", "units": "metre", "component": "t_in_s"},
    {"name": "x", "units": "metre", "component": "t_in_ms"},
    {"name": "x", "units": "metre", "component": "t_in_ks"}
]

CONSTANT_INFO = [
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
    states[0] = 3.0
    states[1] = 7.0
    states[2] = 11.0


def compute_computed_constants(states, rates, constants, computed_constants, algebraic):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    rates[0] = 5.0
    rates[1] = 1000.0*9.0
    rates[2] = 0.001*13.0


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    pass
