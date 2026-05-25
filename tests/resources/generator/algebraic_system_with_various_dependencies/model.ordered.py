# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.8.0"
LIBCELLML_VERSION = "0.6.3"

CONSTANT_COUNT = 2
COMPUTED_CONSTANT_COUNT = 4
ALGEBRAIC_VARIABLE_COUNT = 0

CONSTANT_INFO = [
    {"name": "y", "units": "dimensionless", "component": "my_algebraic_system"},
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_system"}
]

COMPUTED_CONSTANT_INFO = [
    {"name": "a", "units": "dimensionless", "component": "my_algebraic_system"},
    {"name": "c", "units": "dimensionless", "component": "my_algebraic_system"},
    {"name": "b", "units": "dimensionless", "component": "my_algebraic_system"},
    {"name": "d", "units": "dimensionless", "component": "my_algebraic_system"}
]

ALGEBRAIC_VARIABLE_INFO = [
]


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_variables_array():
    return [nan]*ALGEBRAIC_VARIABLE_COUNT


def initialise_arrays(constants, computed_constants, algebraic_variables):
    constants[0] = 5.0
    constants[1] = 3.0


def compute_computed_constants(constants, computed_constants, algebraic_variables):
    computed_constants[0] = 3.0*constants[1]+constants[0]
    computed_constants[1] = 26.6-1.4*computed_constants[0]
    computed_constants[2] = 28.5-0.5*computed_constants[1]-1.5*computed_constants[0]
    computed_constants[3] = computed_constants[2]+computed_constants[1]


def compute_variables(constants, computed_constants, algebraic_variables):
    pass
