# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 1
EXTERNAL_COUNT = 1

CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_eqn"}
]

EXTERNAL_INFO = [
    {"name": "a", "units": "dimensionless", "component": "my_algebraic_eqn"}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(constants, external_variable):
    algebraic[1] = external_variable(variables, 1)


def compute_computed_constants(constants, computed_constants):
    pass


def compute_variables(constants, computed_constants, algebraic, external_variable):
    algebraic[1] = external_variable(variables, 1)
    algebraic[0] = algebraic[1]
