# The content of this file was generated using the Python profile of libCellML 0.4.0.

from enum import Enum
from math import *


__version__ = "0.3.1"
LIBCELLML_VERSION = "0.4.0"

STATE_COUNT = 1
VARIABLE_COUNT = 10


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "x", "units": "dimensionless", "component": "main", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "sin", "units": "dimensionless", "component": "deriv_approx_sin", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "C", "units": "dimensionless", "component": "main", "type": VariableType.CONSTANT},
    {"name": "deriv_approx_initial_value", "units": "dimensionless", "component": "main", "type": VariableType.CONSTANT},
    {"name": "sin", "units": "dimensionless", "component": "actual_sin", "type": VariableType.ALGEBRAIC},
    {"name": "k2_oPi", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "k2Pi", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "kPi_2", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "kPi", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "kPi_32", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "z", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.ALGEBRAIC},
    {"name": "sin", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.ALGEBRAIC}
]


def lt_func(x, y):
    return 1.0 if x < y else 0.0


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, variables):
    variables[0] = 0.75
    variables[1] = 0.0
    variables[3] = 2.0/3.14159265358979
    variables[4] = 2.0*3.14159265358979
    variables[5] = 3.14159265358979/2.0
    variables[6] = 3.14159265358979
    variables[7] = 3.0*3.14159265358979/2.0
    states[0] = variables[1]


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = cos(voi)


def compute_variables(voi, states, rates, variables):
    variables[2] = sin(voi)
    variables[8] = voi*variables[3]-0.5 if lt_func(voi, variables[5]) else (3.14159265358979-voi)*variables[3]-0.5 if lt_func(voi, variables[6]) else (voi-3.14159265358979)*variables[3]-0.5 if lt_func(voi, variables[7]) else (variables[4]-voi)*variables[3]-0.5
    variables[9] = -variables[8]*variables[8]+variables[0]+variables[8] if lt_func(voi, variables[5]) else -variables[8]*variables[8]+variables[0]+variables[8] if lt_func(voi, variables[6]) else variables[8]*variables[8]-variables[0]-variables[8] if lt_func(voi, variables[7]) else variables[8]*variables[8]-variables[0]-variables[8]
