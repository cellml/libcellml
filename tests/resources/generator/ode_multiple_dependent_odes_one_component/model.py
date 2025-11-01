# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 2
CONSTANT_COUNT = 1
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 0

VOI_INFO = {"name": "t", "units": "second", "component": "my_component"}

STATE_INFO = [
    {"name": "y", "units": "dimensionless", "component": "my_component"},
    {"name": "x", "units": "dimensionless", "component": "my_component"}
]

CONSTANT_INFO = [
    {"name": "epsilon", "units": "dimensionless", "component": "my_component"}
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
    states[0] = 0.0
    states[1] = -2.0
    constants[0] = 1.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    rates[1] = states[0]*1.0
    rates[0] = (constants[0]*(1.0-pow(states[1], 2.0))*states[0]-states[1])*1.0


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    pass
