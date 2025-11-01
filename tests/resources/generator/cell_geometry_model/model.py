# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.3"

CONSTANT_COUNT = 2
COMPUTED_CONSTANT_COUNT = 2
ALGEBRAIC_COUNT = 0

CONSTANT_INFO = [
    {"name": "L", "units": "centimeter", "component": "cell_geometry"},
    {"name": "rad", "units": "centimeter", "component": "cell_geometry"}
]

COMPUTED_CONSTANT_INFO = [
    {"name": "vcell", "units": "microlitre", "component": "cell_geometry"},
    {"name": "vss", "units": "microlitre", "component": "cell_geometry"}
]

ALGEBRAIC_INFO = [
]


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def initialise_variables(constants, computed_constants, algebraic):
    constants[0] = 0.01
    constants[1] = 0.0011


def compute_computed_constants(constants, computed_constants):
    computed_constants[0] = 1000.0*3.14*constants[1]*constants[1]*constants[0]
    computed_constants[1] = 0.02*computed_constants[0]


def compute_variables(constants, computed_constants, algebraic):
    pass
