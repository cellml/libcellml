# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 2
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 2

VOI_INFO = {"name": "t", "units": "ms", "component": "environment"}

STATE_INFO = [
    {"name": "y", "units": "mM", "component": "circle_y_implementation"},
    {"name": "x", "units": "mM", "component": "circle_x"}
]

CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_INFO = [
    {"name": "local_complex_maths", "units": "mM", "component": "circle_sibling"},
    {"name": "two_x", "units": "milli_mole", "component": "circle_x_sibling"}
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
    states[1] = 0.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    rates[1] = -states[0]*1.0
    rates[0] = states[1]*1.0


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[0] = states[0]+5.0*states[0]/3.0+1.0*exp(states[0]/2.0)
    algebraic[1] = 2.0*states[1]
