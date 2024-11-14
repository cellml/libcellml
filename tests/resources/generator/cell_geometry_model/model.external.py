# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.6.3"

VARIABLE_COUNT = 4


class VariableType(Enum):
    CONSTANT = 0
    COMPUTED_CONSTANT = 1
    ALGEBRAIC = 2
    EXTERNAL = 3


VARIABLE_INFO = [
    {"name": "vcell", "units": "microlitre", "component": "cell_geometry", "type": VariableType.ALGEBRAIC},
    {"name": "L", "units": "centimeter", "component": "cell_geometry", "type": VariableType.EXTERNAL},
    {"name": "rad", "units": "centimeter", "component": "cell_geometry", "type": VariableType.EXTERNAL},
    {"name": "vss", "units": "microlitre", "component": "cell_geometry", "type": VariableType.ALGEBRAIC}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(variables, external_variable):
    variables[1] = external_variable(variables, 1)
    variables[2] = external_variable(variables, 2)


def compute_computed_constants(variables):
    pass


def compute_variables(variables, external_variable):
    variables[1] = external_variable(variables, 1)
    variables[2] = external_variable(variables, 2)
    variables[0] = 1000.0*3.14*variables[2]*variables[2]*variables[1]
    variables[3] = 0.02*variables[0]
