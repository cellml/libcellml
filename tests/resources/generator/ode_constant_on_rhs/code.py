# The content of this file was generated using the Python profile of libCellML 0.2.0.

from enum import Enum
from math import *


LIBCELLML_VERSION = "0.2.0"

STATE_COUNT = 1
VARIABLE_COUNT = 0


class VariableType(Enum):
    CONSTANT = 1
    COMPUTED_CONSTANT = 2
    ALGEBRAIC = 3

VOI_INFO = {"name": "t", "units": "second", "component": "my_ode"}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_ode"}
]

VARIABLE_INFO = [
]


def create_states_array():
    return [nan]*1


def create_variables_array():
    return [nan]*0


def initialize_states_and_constants(states, variables):
    states[0] = 1.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = 1.0


def compute_variables(voi, states, rates, variables):
    pass
