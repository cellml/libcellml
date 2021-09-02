# The content of this file was generated using the Python profile of libCellML 0.2.0.

from enum import Enum
from math import *


__version__ = "0.3.0"
LIBCELLML_VERSION = "0.2.0"

VARIABLE_COUNT = 4


class VariableType(Enum):
    CONSTANT = 1
    COMPUTED_CONSTANT = 2
    ALGEBRAIC = 3
    EXTERNAL = 4


VARIABLE_INFO = [
    {"name": "L", "units": "centimeter", "component": "cell_geometry", "type": VariableType.EXTERNAL},
    {"name": "rad", "units": "centimeter", "component": "cell_geometry", "type": VariableType.EXTERNAL},
    {"name": "vcell", "units": "microlitre", "component": "cell_geometry", "type": VariableType.ALGEBRAIC},
    {"name": "vss", "units": "microlitre", "component": "cell_geometry", "type": VariableType.ALGEBRAIC}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialise_variables(variables, external_variable):
    variables[0] = external_variable(variables, 0)
    variables[1] = external_variable(variables, 1)


def compute_computed_constants(variables):
    pass


def compute_variables(variables, external_variable):
    variables[0] = external_variable(variables, 0)
    variables[1] = external_variable(variables, 1)
    variables[2] = 1000.0*3.14*variables[1]*variables[1]*variables[0]
    variables[3] = 0.02*variables[2]
