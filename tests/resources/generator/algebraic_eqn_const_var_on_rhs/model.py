# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

CONSTANT_COUNT = 1
COMPUTED_CONSTANT_COUNT = 1
ALGEBRAIC_COUNT = 0

CONSTANT_INFO = [
    {"name": "a", "units": "dimensionless", "component": "my_algebraic_eqn"}
]

COMPUTED_CONSTANT_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_eqn"}
]

ALGEBRAIC_INFO = [
]


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def initialise_variables(constants, algebraic):
    constants[0] = 1.0


def compute_computed_constants(constants, computed_constants):
    computed_constants[0] = constants[0]


def compute_variables(constants, computed_constants, algebraic):
    pass
