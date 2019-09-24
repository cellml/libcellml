# The content of this file was generated using the Python profile of libCellML 0.2.0.

from enum import Enum
from math import *


__version__ = "0.1.0"
LIBCELLML_VERSION = "0.2.0"

STATE_COUNT = 2
VARIABLE_COUNT = 1


class VariableType(Enum):
    CONSTANT = 1
    COMPUTED_CONSTANT = 2
    ALGEBRAIC = 3


VOI_INFO = {"name": "t", "units": "second", "component": "my_component"}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_component"},
    {"name": "y", "units": "dimensionless", "component": "my_component"}
]

VARIABLE_INFO = [
    {"name": "epsilon", "units": "dimensionless", "component": "my_component", "type": VariableType.CONSTANT}
]


def create_states_array():
    return [nan]*2


def create_variables_array():
    return [nan]*1


def initialize_states_and_constants(states, variables):
    states[0] = -2.0
    states[1] = 0.0
    variables[0] = 1.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = states[1]*1.0
    rates[1] = (variables[0]*(1.0-pow(states[0], 2.0))*states[1]-states[0])*1.0


def compute_variables(voi, states, rates, variables):
    pass
