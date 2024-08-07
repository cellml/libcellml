# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 3
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 0


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "t", "units": "second", "component": "environment", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "x", "units": "metre", "component": "t_in_s", "type": VariableType.STATE},
    {"name": "x", "units": "metre", "component": "t_in_ms", "type": VariableType.STATE},
    {"name": "x", "units": "metre", "component": "t_in_ks", "type": VariableType.STATE}
]

VARIABLE_INFO = [
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, rates, constants):
    states[0] = 3.0
    states[1] = 7.0
    states[2] = 11.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    rates[0] = 5.0
    rates[1] = 1000.0*9.0
    rates[2] = 0.001*13.0


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    pass
