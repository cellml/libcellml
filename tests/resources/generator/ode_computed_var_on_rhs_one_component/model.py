# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 1
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 1


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "t", "units": "second", "component": "my_component", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_component", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "a", "units": "per_s", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, rates, constants):
    variables[0] = 1.0
    states[0] = 1.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computedConstants, algebraic):
    rates[0] = variables[0]


def compute_variables(voi, states, rates, constants, computedConstants, algebraic):
    pass
