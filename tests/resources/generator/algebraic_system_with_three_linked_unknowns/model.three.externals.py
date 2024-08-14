# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

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
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_system"},
    {"name": "y", "units": "dimensionless", "component": "my_algebraic_system"},
    {"name": "z", "units": "dimensionless", "component": "my_algebraic_system"}
]


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def create_externals_array():
    return [nan]*EXTERNAL_COUNT


def initialise_variables(constants, external_variable):
    algebraic[0] = external_variable(variables, 0)
    algebraic[1] = external_variable(variables, 1)
    algebraic[2] = external_variable(variables, 2)


def compute_computed_constants(constants, computed_constants):
    pass


def compute_variables(constants, computed_constants, algebraic, external_variable):
    algebraic[0] = external_variable(variables, 0)
    algebraic[1] = external_variable(variables, 1)
    algebraic[2] = external_variable(variables, 2)
