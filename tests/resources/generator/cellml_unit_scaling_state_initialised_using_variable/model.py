# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 2
CONSTANT_COUNT = 2
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 0

VOI_INFO = {"name": "t", "units": "ms", "component": "environment"}

STATE_INFO =     {"name": "k1", "units": "mM", "component": "main"},
    {"name": "k2", "units": "M", "component": "main"}


CONSTANT_INFO = [
    {"name": "k1_cst", "units": "mM", "component": "constants"},
    {"name": "k2_cst", "units": "mM", "component": "constants"}
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


def initialise_variables(states, rates, constants):
    constants[0] = 123.0
    constants[1] = 789.0
    states[0] = constants[0]
    states[1] = 0.001*constants[1]


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    rates[0] = 1.23
    rates[1] = 7.89


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    pass
