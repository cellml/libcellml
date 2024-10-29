# The content of this file was generated using the Python profile of libCellML 0.6.2.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.2"

CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 2
ALGEBRAIC_COUNT = 1
EXTERNAL_COUNT = 1

CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
    {"name": "b", "units": "dimensionless", "component": "my_algebraic_eqn"},
    {"name": "d", "units": "dimensionless", "component": "my_algebraic_eqn"}
]

ALGEBRAIC_INFO = [
    {"name": "a", "units": "dimensionless", "component": "my_algebraic_eqn"}
]

EXTERNAL_INFO = [
    {"name": "c", "units": "dimensionless", "component": "my_algebraic_eqn"}
]


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


def create_externals_array():
    return [nan]*EXTERNAL_COUNT


from nlasolver import nla_solve


def objective_function_0(u, f, data):
    constants = data[0]
    computed_constants = data[1]
    algebraic = data[2]
    externals = data[3]

    algebraic[0] = u[0]

    f[0] = algebraic[0]+computed_constants[0]-(externals[0]+computed_constants[1])


def find_root_0(constants, computed_constants, algebraic, externals):
    u = [nan]*1

    u[0] = algebraic[0]

    u = nla_solve(objective_function_0, u, 1, [constants, computed_constants, algebraic, externals])

    algebraic[0] = u[0]


def initialise_variables(constants, computed_constants, algebraic):
    computed_constants[0] = 3.0
    computed_constants[1] = 7.0
    algebraic[0] = 1.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_variables(constants, computed_constants, algebraic, externals, external_variable):
    externals[0] = external_variable(constants, computed_constants, algebraic, externals, 0)
    find_root_0(constants, computed_constants, algebraic, externals)
