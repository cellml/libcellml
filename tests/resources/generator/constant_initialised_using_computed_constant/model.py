# The content of this file was generated using the Python profile of libCellML 0.7.1.

from enum import Enum
from math import *


__version__ = "0.8.0"
LIBCELLML_VERSION = "0.7.1"

STATE_COUNT = 1
CONSTANT_COUNT = 3
COMPUTED_CONSTANT_COUNT = 3
ALGEBRAIC_VARIABLE_COUNT = 0

VOI_INFO = {"name": "t", "units": "dimensionless", "component": "main"}

STATE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "main"}
]

CONSTANT_INFO = [
    {"name": "kkc", "units": "dimensionless", "component": "main"},
    {"name": "kc", "units": "dimensionless", "component": "main"},
    {"name": "k", "units": "dimensionless", "component": "main"}
]

COMPUTED_CONSTANT_INFO = [
    {"name": "cc2", "units": "dimensionless", "component": "main"},
    {"name": "cc3", "units": "dimensionless", "component": "main"},
    {"name": "cc", "units": "dimensionless", "component": "main"}
]

ALGEBRAIC_VARIABLE_INFO = [
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_variables_array():
    return [nan]*ALGEBRAIC_VARIABLE_COUNT


def initialise_arrays(states, rates, constants, computed_constants, algebraic_variables):
    constants[2] = 3.0


def compute_computed_constants(voi, states, rates, constants, computed_constants, algebraic_variables):
    computed_constants[2] = 2.0*constants[2]
    constants[1] = computed_constants[2]
    computed_constants[0] = 3.0*constants[1]
    computed_constants[1] = computed_constants[0]+1.0
    states[0] = computed_constants[1]
    constants[0] = constants[1]


def compute_rates(voi, states, rates, constants, computed_constants, algebraic_variables):
    rates[0] = constants[1]+constants[0]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic_variables):
    pass
