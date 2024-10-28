# The content of this file was generated using the Python profile of libCellML 0.6.1.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.1"

CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 3

CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_system"},
    {"name": "y", "units": "dimensionless", "component": "my_algebraic_system"},
    {"name": "z", "units": "dimensionless", "component": "my_algebraic_system"}
]


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


from nlasolver import nla_solve


def objective_function_0(u, f, data):
    constants = data[0]
    computed_constants = data[1]
    algebraic = data[2]

    algebraic[0] = u[0]
    algebraic[1] = u[1]
    algebraic[2] = u[2]

    f[0] = 2.0*algebraic[0]+algebraic[1]-2.0*algebraic[2]-(-1.0)
    f[1] = 3.0*algebraic[0]-3.0*algebraic[1]-algebraic[2]-5.0
    f[2] = algebraic[0]-2.0*algebraic[1]+3.0*algebraic[2]-6.0


def find_root_0(constants, computed_constants, algebraic):
    u = [nan]*3

    u[0] = algebraic[0]
    u[1] = algebraic[1]
    u[2] = algebraic[2]

    u = nla_solve(objective_function_0, u, 3, [constants, computed_constants, algebraic])

    algebraic[0] = u[0]
    algebraic[1] = u[1]
    algebraic[2] = u[2]


def initialise_variables(constants, computed_constants, algebraic):
    algebraic[0] = 1.0
    algebraic[1] = 1.0
    algebraic[2] = 1.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_variables(constants, computed_constants, algebraic):
    find_root_0(constants, computed_constants, algebraic)
