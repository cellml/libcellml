# The content of this file was generated using the Python profile of libCellML 0.2.0.

from enum import Enum
from math import *


__version__ = "0.2.0"
LIBCELLML_VERSION = "0.2.0"

STATE_COUNT = 0
VARIABLE_COUNT = 3


class VariableType(Enum):
    CONSTANT = 1
    COMPUTED_CONSTANT = 2
    ALGEBRAIC = 3


VOI_INFO = {"name": "", "units": "", "component": ""}

STATE_INFO = [
]

VARIABLE_INFO = [
    {"name": "k", "units": "mM", "component": "constants", "type": VariableType.CONSTANT},
    {"name": "x", "units": "mM", "component": "main", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "y", "units": "M", "component": "main", "type": VariableType.COMPUTED_CONSTANT}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_states_and_constants(states, variables):
    variables[0] = 123.0


def compute_computed_constants(variables):
    variables[1] = variables[0]+variables[0]
    variables[2] = 0.001*variables[0]+0.001*variables[0]


def compute_rates(voi, states, rates, variables):
    pass


def compute_variables(voi, states, rates, variables):
    pass
