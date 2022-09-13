# The content of this file was generated using the Python profile of libCellML 0.3.102.

from enum import Enum
from math import *


__version__ = "0.3.0"
LIBCELLML_VERSION = "0.3.102"

VARIABLE_COUNT = 4


class VariableType(Enum):
    CONSTANT = 1
    COMPUTED_CONSTANT = 2
    ALGEBRAIC = 3


VARIABLE_INFO = [
    {"name": "L", "units": "centimeter", "component": "cell_geometry", "type": VariableType.CONSTANT},
    {"name": "rad", "units": "centimeter", "component": "cell_geometry", "type": VariableType.CONSTANT},
    {"name": "vcell", "units": "microlitre", "component": "cell_geometry", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "vss", "units": "microlitre", "component": "cell_geometry", "type": VariableType.COMPUTED_CONSTANT}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(variables):
    variables[0] = 0.01
    variables[1] = 0.0011


def compute_computed_constants(variables):
    variables[2] = 1000.0*3.14*variables[1]*variables[1]*variables[0]
    variables[3] = 0.02*variables[2]


def compute_variables(variables):
    pass
