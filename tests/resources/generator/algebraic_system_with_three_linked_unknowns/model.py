# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 3


class VariableType(Enum):
    CONSTANT = 0
    COMPUTED_CONSTANT = 1
    ALGEBRAIC = 2


CONSTANT_INFO = [
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.ALGEBRAIC},
    {"name": "y", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.ALGEBRAIC},
    {"name": "z", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.ALGEBRAIC}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


from nlasolver import nla_solve


def objective_function_0(u, f, data):
    variables = data[0]

    algebraic[0] = u[0]
    algebraic[1] = u[1]
    algebraic[2] = u[2]

    f[0] = 2.0*algebraic[0]+algebraic[1]-2.0*algebraic[2]-(-1.0)
    f[1] = 3.0*algebraic[0]-3.0*algebraic[1]-algebraic[2]-5.0
    f[2] = algebraic[0]-2.0*algebraic[1]+3.0*algebraic[2]-6.0


def find_root_0(variables):
    u = [nan]*3

    u[0] = algebraic[0]
    u[1] = algebraic[1]
    u[2] = algebraic[2]

    u = nla_solve(objective_function_0, u, 3, [variables])

    algebraic[0] = u[0]
    algebraic[1] = u[1]
    algebraic[2] = u[2]


def initialise_variables(constants):
    algebraic[0] = 1.0
    algebraic[1] = 1.0
    algebraic[2] = 1.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_variables(constants, computed_constants, algebraic):
    find_root_0(variables)
