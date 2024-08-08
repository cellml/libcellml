# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 1
CONSTANT_COUNT = 2
COMPUTED_CONSTANT_COUNT = 5
ALGEBRAIC_COUNT = 3


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
    {"name": "deriv_approx_initial_value", "units": "dimensionless", "component": "main", "type": VariableType.CONSTANT},
    {"name": "C", "units": "dimensionless", "component": "main", "type": VariableType.CONSTANT},
    {"name": "k2_oPi", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "k2Pi", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "kPi_2", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "kPi", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "kPi_32", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "sin", "units": "dimensionless", "component": "actual_sin", "type": VariableType.ALGEBRAIC},
    {"name": "sin", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.ALGEBRAIC},
    {"name": "z", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.ALGEBRAIC}
]


def lt_func(x, y):
    return 1.0 if x < y else 0.0


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, rates, constants):
    constants[0] = 0.0
    constants[1] = 0.75
    computed_constants[0] = 2.0/3.14159265358979
    computed_constants[1] = 2.0*3.14159265358979
    computed_constants[2] = 3.14159265358979/2.0
    computed_constants[3] = 3.14159265358979
    computed_constants[4] = 3.0*3.14159265358979/2.0
    states[0] = constants[0]


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    rates[0] = cos(voi)


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[0] = sin(voi)
    algebraic[2] = voi*computed_constants[0]-0.5 if lt_func(voi, computed_constants[2]) else (3.14159265358979-voi)*computed_constants[0]-0.5 if lt_func(voi, computed_constants[3]) else (voi-3.14159265358979)*computed_constants[0]-0.5 if lt_func(voi, computed_constants[4]) else (computed_constants[1]-voi)*computed_constants[0]-0.5
    algebraic[1] = -algebraic[2]*algebraic[2]+constants[1]+algebraic[2] if lt_func(voi, computed_constants[2]) else -algebraic[2]*algebraic[2]+constants[1]+algebraic[2] if lt_func(voi, computed_constants[3]) else algebraic[2]*algebraic[2]-constants[1]-algebraic[2] if lt_func(voi, computed_constants[4]) else algebraic[2]*algebraic[2]-constants[1]-algebraic[2]
