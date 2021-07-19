# The content of this file was generated using the Python profile of libCellML 0.2.0.

from enum import Enum
from math import *


__version__ = "0.3.0"
LIBCELLML_VERSION = "0.2.0"

VARIABLE_COUNT = 1


class VariableType(Enum):
    CONSTANT = 1
    COMPUTED_CONSTANT = 2
    ALGEBRAIC = 3


VARIABLE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_component", "type": VariableType.COMPUTED_CONSTANT}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_constants(variables):
    variables[0] = 1.0


def compute_computed_constants(variables):
    pass


def compute_variables(variables):
    pass
