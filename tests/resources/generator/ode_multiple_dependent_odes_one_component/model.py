# The content of this file was generated using the Python profile of libCellML 0.6.2.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.6.2"

STATE_COUNT = 2
VARIABLE_COUNT = 1


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "t", "units": "second", "component": "my_component", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_component", "type": VariableType.STATE},
    {"name": "y", "units": "dimensionless", "component": "my_component", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "epsilon", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, rates, variables):
    variables[0] = 1.0
    states[0] = -2.0
    states[1] = 0.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = states[1]*1.0
    rates[1] = (variables[0]*(1.0-pow(states[0], 2.0))*states[1]-states[0])*1.0


def compute_variables(voi, states, rates, variables):
    pass
