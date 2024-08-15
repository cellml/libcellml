# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 2
EXTERNAL_COUNT = 2

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


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def create_externals_array():
    return [nan]*EXTERNAL_COUNT


def initialise_variables(constants, algebraic, external_variable):
    algebraic[1] = external_variable(variables, 1)
    algebraic[2] = external_variable(variables, 2)


def compute_computed_constants(constants, computed_constants):
    pass


def compute_variables(constants, computed_constants, algebraic, external_variable):
    algebraic[1] = external_variable(variables, 1)
    algebraic[2] = external_variable(variables, 2)
    algebraic[0] = 1000.0*3.14*algebraic[2]*algebraic[2]*algebraic[1]
    algebraic[3] = 0.02*algebraic[0]
