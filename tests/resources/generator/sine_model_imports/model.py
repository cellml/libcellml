# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 1
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 10


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
    {"name": "sin", "units": "dimensionless", "component": "actual_sin", "type": VariableType.ALGEBRAIC},
    {"name": "deriv_approx_initial_value", "units": "dimensionless", "component": "main", "type": VariableType.CONSTANT},
    {"name": "sin", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.ALGEBRAIC},
    {"name": "C", "units": "dimensionless", "component": "main", "type": VariableType.CONSTANT},
    {"name": "k2_oPi", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "k2Pi", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "kPi_2", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "kPi", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "kPi_32", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "z", "units": "dimensionless", "component": "parabolic_approx_sin", "type": VariableType.ALGEBRAIC}
]


def lt_func(x, y):
    return 1.0 if x < y else 0.0


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(states, rates, constants):
    constants[1] = 0.0
    constants[3] = 0.75
    computed_constants[4] = 2.0/3.14159265358979
    computed_constants[5] = 2.0*3.14159265358979
    computed_constants[6] = 3.14159265358979/2.0
    computed_constants[7] = 3.14159265358979
    computed_constants[8] = 3.0*3.14159265358979/2.0
    states[0] = constants[1]


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    rates[0] = cos(voi)


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[0] = sin(voi)
    algebraic[9] = voi*computed_constants[4]-0.5 if lt_func(voi, computed_constants[6]) else (3.14159265358979-voi)*computed_constants[4]-0.5 if lt_func(voi, computed_constants[7]) else (voi-3.14159265358979)*computed_constants[4]-0.5 if lt_func(voi, computed_constants[8]) else (computed_constants[5]-voi)*computed_constants[4]-0.5
    algebraic[2] = -algebraic[9]*algebraic[9]+constants[3]+algebraic[9] if lt_func(voi, computed_constants[6]) else -algebraic[9]*algebraic[9]+constants[3]+algebraic[9] if lt_func(voi, computed_constants[7]) else algebraic[9]*algebraic[9]-constants[3]-algebraic[9] if lt_func(voi, computed_constants[8]) else algebraic[9]*algebraic[9]-constants[3]-algebraic[9]
