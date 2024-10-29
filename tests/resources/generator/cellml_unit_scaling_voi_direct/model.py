# The content of this file was generated using the Python profile of libCellML 0.6.2.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.6.2"

STATE_COUNT = 2
VARIABLE_COUNT = 0


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "t", "units": "ms", "component": "environment", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "main", "type": VariableType.STATE},
    {"name": "y", "units": "dimensionless", "component": "main", "type": VariableType.STATE}
]

VARIABLE_INFO = [
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, rates, variables):
    states[0] = 3.0
    states[1] = 5.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = voi/1.0
    rates[1] = 0.001*voi/1.0


def compute_variables(voi, states, rates, variables):
    pass
