# The content of this file was generated using the Python profile of libCellML 0.2.0.

from enum import Enum
from math import *


__version__ = "0.1.0"
LIBCELLML_VERSION = "0.2.0"

STATE_COUNT = 2
VARIABLE_COUNT = 0


class VariableType(Enum):
    CONSTANT = 1
    COMPUTED_CONSTANT = 2
    ALGEBRAIC = 3


VOI_INFO = {"name": "t", "units": "ms", "component": "environment"}

STATE_INFO = [
    {"name": "x", "units": "mM", "component": "t_in_ms"},
    {"name": "x", "units": "mM", "component": "t_in_s"}
]

VARIABLE_INFO = [
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialize_states_and_constants(states, variables):
    states[0] = 3.0
    states[1] = 7.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = 5.0
    rates[1] = 1000.0*9.0


def compute_variables(voi, states, rates, variables):
    pass
