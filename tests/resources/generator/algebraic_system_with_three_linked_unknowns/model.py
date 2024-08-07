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


VARIABLE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.ALGEBRAIC},
    {"name": "y", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.ALGEBRAIC},
    {"name": "z", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.ALGEBRAIC}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


from nlasolver import nla_solve


def objective_function_0(u, f, data):
    variables = data[0]

    variables[0] = u[0]
    variables[1] = u[1]
    variables[2] = u[2]

    f[0] = 2.0*variables[0]+variables[1]-2.0*variables[2]-(-1.0)
    f[1] = 3.0*variables[0]-3.0*variables[1]-variables[2]-5.0
    f[2] = variables[0]-2.0*variables[1]+3.0*variables[2]-6.0


def find_root_0(variables):
    u = [nan]*3

    u[0] = variables[0]
    u[1] = variables[1]
    u[2] = variables[2]

    u = nla_solve(objective_function_0, u, 3, [variables])

    variables[0] = u[0]
    variables[1] = u[1]
    variables[2] = u[2]


def initialise_variables(constants):
    variables[0] = 1.0
    variables[1] = 1.0
    variables[2] = 1.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_variables(constants, computed_constants, algebraic):
    find_root_0(variables)
