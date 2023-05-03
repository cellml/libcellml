# The content of this file was generated using the Python profile of libCellML 0.4.0.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.4.0"

VARIABLE_COUNT = 2


class VariableType(Enum):
    CONSTANT = 0
    COMPUTED_CONSTANT = 1
    ALGEBRAIC = 2
    EXTERNAL = 3


VARIABLE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.ALGEBRAIC},
    {"name": "a", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.EXTERNAL}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(variables, external_variable):
    variables[1] = external_variable(variables, 1)


def compute_computed_constants(variables):
    pass


def compute_variables(variables, external_variable):
    variables[1] = external_variable(variables, 1)
    variables[0] = variables[1]
