# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

CONSTANT_COUNT = 2
COMPUTED_CONSTANT_COUNT = 1
ALGEBRAIC_COUNT = 3

CONSTANT_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_system"},
    {"name": "y", "units": "dimensionless", "component": "my_algebraic_system"}
]

COMPUTED_CONSTANT_INFO = [
    {"name": "a", "units": "dimensionless", "component": "my_algebraic_system"}
]

ALGEBRAIC_INFO = [
    {"name": "c", "units": "dimensionless", "component": "my_algebraic_system"},
    {"name": "b", "units": "dimensionless", "component": "my_algebraic_system"},
    {"name": "d", "units": "dimensionless", "component": "my_algebraic_system"}
]


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


from nlasolver import nla_solve


def objective_function_0(u, f, data):
    variables = data[0]

    algebraic[0] = u[0]
    algebraic[1] = u[1]

    f[0] = 3.0*computed_constants[0]+2.0*algebraic[1]+algebraic[0]-57.0
    f[1] = computed_constants[0]+3.0*algebraic[1]-algebraic[0]-19.0


def find_root_0(variables):
    u = [nan]*2

    u[0] = algebraic[0]
    u[1] = algebraic[1]

    u = nla_solve(objective_function_0, u, 2, [variables])

    algebraic[0] = u[0]
    algebraic[1] = u[1]


def initialise_variables(constants, algebraic):
    constants[0] = 3.0
    constants[1] = 5.0
    algebraic[0] = 1.0
    algebraic[1] = 1.0


def compute_computed_constants(constants, computed_constants):
    computed_constants[0] = 3.0*constants[0]+constants[1]


def compute_variables(constants, computed_constants, algebraic):
    find_root_0(variables)
    algebraic[2] = algebraic[1]+algebraic[0]
