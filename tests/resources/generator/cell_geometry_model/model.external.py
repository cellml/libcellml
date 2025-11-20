# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.6.0"
LIBCELLML_VERSION = "0.6.3"

CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_VARIABLE_COUNT = 2
EXTERNAL_VARIABLE_COUNT = 2

CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_INFO = [
    {"name": "vcell", "units": "microlitre", "component": "cell_geometry"},
    {"name": "vss", "units": "microlitre", "component": "cell_geometry"}
]

EXTERNAL_INFO = [
    {"name": "L", "units": "centimeter", "component": "cell_geometry"},
    {"name": "rad", "units": "centimeter", "component": "cell_geometry"}
]


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_variables_array():
    return [nan]*ALGEBRAIC_VARIABLE_COUNT


def create_external_variables_array():
    return [nan]*EXTERNAL_VARIABLE_COUNT


def initialise_arrays(constants, computed_constants, algebraic_variables):
    pass


def compute_computed_constants(constants, computed_constants, algebraic):
    pass


def compute_variables(constants, computed_constants, algebraic_variables, external_variables, external_variable):
    externalVariables[0] = external_variable(constants, computed_constants, algebraic_variables, external_variables, 0)
    externalVariables[1] = external_variable(constants, computed_constants, algebraic_variables, external_variables, 1)
    algebraicVariables[0] = 1000.0*3.14*externalVariables[1]*externalVariables[1]*externalVariables[0]
    algebraicVariables[1] = 0.02*algebraicVariables[0]
