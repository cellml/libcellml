# The content of this file was generated using the Python profile of libCellML 0.3.103.

from enum import Enum
from math import *


__version__ = "0.3.0"
LIBCELLML_VERSION = "0.3.103"

STATE_COUNT = 2
VARIABLE_COUNT = 2


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 1
    STATE = 2
    CONSTANT = 3
    COMPUTED_CONSTANT = 4
    ALGEBRAIC = 5


VOI_INFO = {"name": "t", "units": "ms", "component": "environment", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "x", "units": "mM", "component": "circle_x", "type": VariableType.STATE},
    {"name": "y", "units": "mM", "component": "circle_y_implementation", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "local_complex_maths", "units": "mM", "component": "circle_sibling", "type": VariableType.ALGEBRAIC},
    {"name": "two_x", "units": "milli_mole", "component": "circle_x_sibling", "type": VariableType.ALGEBRAIC}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, variables):
    states[0] = 0.0
    states[1] = 1.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = -states[1]*1.0
    rates[1] = states[0]*1.0


def compute_variables(voi, states, rates, variables):
    variables[0] = states[1]+5.0*states[1]/3.0+1.0*exp(states[1]/2.0)
    variables[1] = 2.0*states[0]
