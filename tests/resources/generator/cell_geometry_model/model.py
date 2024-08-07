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


VARIABLE_INFO = [
    {"name": "vcell", "units": "microlitre", "component": "cell_geometry", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "L", "units": "centimeter", "component": "cell_geometry", "type": VariableType.CONSTANT},
    {"name": "rad", "units": "centimeter", "component": "cell_geometry", "type": VariableType.CONSTANT},
    {"name": "vss", "units": "microlitre", "component": "cell_geometry", "type": VariableType.COMPUTED_CONSTANT}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(constants):
    variables[1] = 0.01
    variables[2] = 0.0011


def compute_computed_constants(constants, computed_constants):
    variables[0] = 1000.0*3.14*variables[2]*variables[2]*variables[1]
    variables[3] = 0.02*variables[0]


def compute_variables(constants, computedConstants, algebraic):
    pass
