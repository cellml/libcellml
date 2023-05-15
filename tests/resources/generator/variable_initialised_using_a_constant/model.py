# The content of this file was generated using the Python profile of libCellML 0.4.0.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.4.0"

STATE_COUNT = 1
VARIABLE_COUNT = 1


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "t", "units": "second", "component": "component_1", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "X", "units": "dimensionless", "component": "component_1", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "X_init", "units": "dimensionless", "component": "component_2", "type": VariableType.CONSTANT}
]


def create_states_array():
    return [0.0]*STATE_COUNT


def create_variables_array():
    return [0.0]*VARIABLE_COUNT


def initialise_variables(states, variables):
    variables[0] = 7.0
    states[0] = variables[0]


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = 3.0


def compute_variables(voi, states, rates, variables):
    pass
