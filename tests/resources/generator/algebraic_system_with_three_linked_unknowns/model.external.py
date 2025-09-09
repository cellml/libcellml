# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.6.0"
LIBCELLML_VERSION = "0.6.3"

CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 0
EXTERNAL_COUNT = 3

CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_INFO = [
]

EXTERNAL_INFO = [
    {"name": "z", "units": "dimensionless", "component": "my_algebraic_system"},
    {"name": "y", "units": "dimensionless", "component": "my_algebraic_system"},
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_system"}
]


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def create_externals_array():
    return [nan]*EXTERNAL_COUNT


def initialise_variables(constants, computed_constants, algebraic):
    pass


def compute_computed_constants(states, rates, constants, computed_constants, algebraic):
    pass


def compute_variables(constants, computed_constants, algebraic, externals, external_variable):
    externals[0] = external_variable(constants, computed_constants, algebraic, externals, 0)
    externals[1] = external_variable(constants, computed_constants, algebraic, externals, 1)
    externals[2] = external_variable(constants, computed_constants, algebraic, externals, 2)
