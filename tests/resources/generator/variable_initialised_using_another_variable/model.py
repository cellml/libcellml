# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.8.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 13
CONSTANT_COUNT = 2
COMPUTED_CONSTANT_COUNT = 1
ALGEBRAIC_VARIABLE_COUNT = 0

VOI_INFO = {"name": "t", "units": "dimensionless", "component": "main"}

STATE_INFO = [
    {"name": "xStateStateCst", "units": "dimensionless", "component": "main"},
    {"name": "kStateStateCst", "units": "dimensionless", "component": "main"},
    {"name": "xStateStateCompCst", "units": "dimensionless", "component": "main"},
    {"name": "kStateStateCompCst", "units": "dimensionless", "component": "main"},
    {"name": "xStateStateState", "units": "dimensionless", "component": "main"},
    {"name": "kStateStateState", "units": "dimensionless", "component": "main"},
    {"name": "xStateStateNla", "units": "dimensionless", "component": "main"},
    {"name": "kStateStateNla", "units": "dimensionless", "component": "main"},
    {"name": "xStateCst", "units": "dimensionless", "component": "main"},
    {"name": "xStateCompCst", "units": "dimensionless", "component": "main"},
    {"name": "xStateState", "units": "dimensionless", "component": "main"},
    {"name": "kStateState", "units": "dimensionless", "component": "main"},
    {"name": "xStateNla", "units": "dimensionless", "component": "main"}
]

CONSTANT_INFO = [
    {"name": "kStateCst", "units": "dimensionless", "component": "main"},
    {"name": "kStateNla", "units": "dimensionless", "component": "main"}
]

COMPUTED_CONSTANT_INFO = [
    {"name": "kStateCompCst", "units": "dimensionless", "component": "main"}
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
    constants[0] = 3.0
    states[1] = constants[0]
    states[0] = states[1]
    states[11] = 5.0
    states[5] = states[11]
    states[4] = states[5]
    constants[1] = 7.0
    states[7] = constants[1]
    states[6] = states[7]
    states[8] = constants[0]
    states[10] = states[11]
    states[12] = constants[1]


def compute_computed_constants(voi, states, rates, constants, computed_constants, algebraic_variables):
    computed_constants[0] = 1.23*constants[0]
    states[3] = computed_constants[0]
    states[2] = states[3]
    states[9] = computed_constants[0]


def compute_rates(voi, states, rates, constants, computed_constants, algebraic_variables):
    rates[0] = 1.23
    rates[1] = 1.23
    rates[2] = 1.23
    rates[3] = 1.23
    rates[4] = 1.23
    rates[5] = 1.23
    rates[6] = 1.23
    rates[7] = 1.23
    rates[8] = 1.23
    rates[9] = 1.23
    rates[10] = 1.23
    rates[11] = 1.23
    rates[12] = 1.23


def compute_variables(voi, states, rates, constants, computed_constants, algebraic_variables):
    pass
