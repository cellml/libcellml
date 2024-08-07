# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.5.0"

CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 4


class VariableType(Enum):
    CONSTANT = 0
    COMPUTED_CONSTANT = 1
    ALGEBRAIC = 2
    EXTERNAL = 3


VARIABLE_INFO = [
    {"name": "b", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "c", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "d", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "a", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.EXTERNAL}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(constants, external_variable):
    variables[0] = 3.0
    variables[1] = 5.0
    variables[2] = 7.0
    variables[3] = external_variable(variables, 3)


def compute_computed_constants(constants, computed_constants):
    pass


def compute_variables(constants, computedConstants, algebraic, external_variable):
    variables[3] = external_variable(variables, 3)
