# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 3
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 4


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "t", "units": "dimensionless", "component": "main", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "y1", "units": "dimensionless", "component": "main", "type": VariableType.STATE},
    {"name": "y3", "units": "dimensionless", "component": "main", "type": VariableType.STATE},
    {"name": "y2", "units": "dimensionless", "component": "main", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "k1", "units": "dimensionless", "component": "main", "type": VariableType.CONSTANT},
    {"name": "k3", "units": "dimensionless", "component": "main", "type": VariableType.CONSTANT},
    {"name": "k2", "units": "dimensionless", "component": "main", "type": VariableType.CONSTANT},
    {"name": "y2_scaled", "units": "dimensionless", "component": "main", "type": VariableType.ALGEBRAIC}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, rates, constants):
    variables[0] = 0.04
    variables[1] = 1.0e4
    variables[2] = 3.0e7
    states[0] = 1.0
    states[1] = 0.0
    states[2] = 0.0


def compute_computed_constants(computed_constants):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = -variables[0]*states[0]+variables[1]*states[2]*states[1]
    rates[2] = variables[0]*states[0]-variables[2]*pow(states[2], 2.0)-variables[1]*states[2]*states[1]
    rates[1] = variables[2]*pow(states[2], 2.0)


def compute_variables(voi, states, rates, variables):
    variables[3] = 10000.0*states[2]
