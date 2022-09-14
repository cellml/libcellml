# The content of this file was generated using the Python profile of libCellML 0.3.103.

from enum import Enum
from math import *


__version__ = "0.3.0"
LIBCELLML_VERSION = "0.3.103"

VARIABLE_COUNT = 2


class VariableType(Enum):
    CONSTANT = 1
    COMPUTED_CONSTANT = 2
    ALGEBRAIC = 3
    EXTERNAL = 4


VARIABLE_INFO = [
    {"name": "a", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.EXTERNAL},
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.ALGEBRAIC}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(variables, external_variable):
    variables[0] = external_variable(variables, 0)


def compute_computed_constants(variables):
    pass


def compute_variables(variables, external_variable):
    variables[0] = external_variable(variables, 0)
    variables[1] = variables[0]
