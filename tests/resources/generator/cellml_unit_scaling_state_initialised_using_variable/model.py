# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 2
VARIABLE_COUNT = 2


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "t", "units": "ms", "component": "environment", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "k1", "units": "mM", "component": "main", "type": VariableType.STATE},
    {"name": "k2", "units": "M", "component": "main", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "k1_cst", "units": "mM", "component": "constants", "type": VariableType.CONSTANT},
    {"name": "k2_cst", "units": "mM", "component": "constants", "type": VariableType.CONSTANT}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, rates, variables):
    variables[0] = 123.0
    variables[1] = 789.0
    states[0] = variables[0]
    states[1] = 0.001*variables[1]


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = 1.23
    rates[1] = 7.89


def compute_variables(voi, states, rates, variables):
    pass
