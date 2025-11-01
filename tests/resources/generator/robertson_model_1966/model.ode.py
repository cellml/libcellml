# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.6.0"
LIBCELLML_VERSION = "0.6.3"

STATE_COUNT = 3
CONSTANT_COUNT = 3
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 1

VOI_INFO = {"name": "t", "units": "dimensionless", "component": "main"}

STATE_INFO = [
    {"name": "y3", "units": "dimensionless", "component": "main"},
    {"name": "y2", "units": "dimensionless", "component": "main"},
    {"name": "y1", "units": "dimensionless", "component": "main"}
]

CONSTANT_INFO = [
    {"name": "k3", "units": "dimensionless", "component": "main"},
    {"name": "k1", "units": "dimensionless", "component": "main"},
    {"name": "k2", "units": "dimensionless", "component": "main"}
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_INFO = [
    {"name": "y2_scaled", "units": "dimensionless", "component": "main"}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def initialise_variables(states, rates, constants, computed_constants, algebraic):
    states[0] = 0.0
    states[1] = 0.0
    states[2] = 1.0
    constants[0] = 1.0e4
    constants[1] = 0.04
    constants[2] = 3.0e7


def compute_computed_constants(states, rates, constants, computed_constants, algebraic):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    rates[2] = -constants[1]*states[2]+constants[0]*states[1]*states[0]
    rates[1] = constants[1]*states[2]-constants[2]*pow(states[1], 2.0)-constants[0]*states[1]*states[0]
    rates[0] = constants[2]*pow(states[1], 2.0)


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    algebraic[0] = 10000.0*states[1]
