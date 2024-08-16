# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 1
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 2

VOI_INFO = {"name": "time", "units": "second", "component": "my_component"}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_component"}
]

CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_INFO = [
    {"name": "a", "units": "second", "component": "my_component"},
    {"name": "b", "units": "second", "component": "my_component"}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def initialise_variables(voi, states, rates, constants, algebraic):
    states[0] = 0.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    rates[0] = 1.0


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[1] = 2.0*voi
    algebraic[0] = 3.0*algebraic[1]
