# The content of this file was generated using the Python profile of libCellML 0.2.0.

from enum import Enum
from math import *


__version__ = "0.1.0"
LIBCELLML_VERSION = "0.2.0"

STATE_COUNT = 4
VARIABLE_COUNT = 1


class VariableType(Enum):
    CONSTANT = 1
    COMPUTED_CONSTANT = 2
    ALGEBRAIC = 3


VOI_INFO = {"name": "t", "units": "ms", "component": "environment"}

STATE_INFO = [
    {"name": "x", "units": "mV", "component": "t"},
    {"name": "scaled_x", "units": "volt", "component": "t"},
    {"name": "x", "units": "mV", "component": "scaled_t"},
    {"name": "scaled_x", "units": "volt", "component": "scaled_t"}
]

VARIABLE_INFO = [
    {"name": "k", "units": "mV", "component": "constants", "type": VariableType.CONSTANT}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialize_states_and_constants(states, variables):
    states[0] = 0.0
    states[1] = 0.0
    states[2] = 0.0
    states[3] = 0.0
    variables[0] = 123.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = variables[0]
    rates[1] = 0.001*variables[0]
    rates[2] = 1000.0*variables[0]
    rates[3] = 1000.0*0.001*variables[0]


def compute_variables(voi, states, rates, variables):
    pass
