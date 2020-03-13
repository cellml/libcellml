# The content of this file was generated using the Python profile of libCellML 0.2.0.

from enum import Enum
from math import *


__version__ = "0.1.0"
LIBCELLML_VERSION = "0.2.0"

STATE_COUNT = 3
VARIABLE_COUNT = 0


class VariableType(Enum):
    CONSTANT = 1
    COMPUTED_CONSTANT = 2
    ALGEBRAIC = 3


VOI_INFO = {"name": "t", "units": "ms", "component": "environment"}

STATE_INFO = [
    {"name": "k", "units": "mM", "component": "states"},
    {"name": "x", "units": "mM", "component": "main"},
    {"name": "y", "units": "M", "component": "main"}
]

VARIABLE_INFO = [
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialize_states_and_constants(states, variables):
    states[0] = 123.0
    states[1] = 3.0
    states[2] = 5.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = 789.0
    rates[1] = states[0]+states[0]
    rates[2] = 0.001*states[0]+0.001*states[0]


def compute_variables(voi, states, rates, variables):
    pass
