# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 2
ALGEBRAIC_COUNT = 0


class VariableType(Enum):
    CONSTANT = 0
    COMPUTED_CONSTANT = 1
    ALGEBRAIC = 2


CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "a", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.COMPUTED_CONSTANT}
]

ALGEBRAIC_INFO = [
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(constants):
    computed_constants[1] = 1.0


def compute_computed_constants(constants, computed_constants):
    computed_constants[0] = computed_constants[1]


def compute_variables(constants, computed_constants, algebraic):
    pass
