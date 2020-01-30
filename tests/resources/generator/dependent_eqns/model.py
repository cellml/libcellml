# The content of this file was generated using the Python profile of libCellML 0.2.0.

from enum import Enum
from math import *


__version__ = "0.1.0"
LIBCELLML_VERSION = "0.2.0"

STATE_COUNT = 1
VARIABLE_COUNT = 2


class VariableType(Enum):
    CONSTANT = 1
    COMPUTED_CONSTANT = 2
    ALGEBRAIC = 3


VOI_INFO = {"name": "time", "units": "second", "component": "my_component"}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_component"}
]

VARIABLE_INFO = [
    {"name": "b", "units": "second", "component": "my_component", "type": VariableType.ALGEBRAIC},
    {"name": "a", "units": "second", "component": "my_component", "type": VariableType.ALGEBRAIC}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialize_states_and_constants(states, variables):
    states[0] = 0.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = 1.0


def compute_variables(voi, states, rates, variables):
    variables[0] = 2.0*voi
    variables[1] = 3.0*variables[0]
