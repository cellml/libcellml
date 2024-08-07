# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.5.0"

CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 6


class VariableType(Enum):
    CONSTANT = 0
    COMPUTED_CONSTANT = 1
    ALGEBRAIC = 2


VARIABLE_INFO = [
    {"name": "d", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.ALGEBRAIC},
    {"name": "b", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.ALGEBRAIC},
    {"name": "c", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.ALGEBRAIC},
    {"name": "a", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.CONSTANT},
    {"name": "y", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.CONSTANT}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


from nlasolver import nla_solve


def objective_function_0(u, f, data):
    variables = data[0]

    variables[2] = u[0]
    variables[1] = u[1]

    f[0] = 3.0*variables[3]+2.0*variables[1]+variables[2]-57.0
    f[1] = variables[3]+3.0*variables[1]-variables[2]-19.0


def find_root_0(variables):
    u = [nan]*2

    u[0] = variables[2]
    u[1] = variables[1]

    u = nla_solve(objective_function_0, u, 2, [variables])

    variables[2] = u[0]
    variables[1] = u[1]


def initialise_variables(constants):
    variables[1] = 1.0
    variables[2] = 1.0
    variables[4] = 3.0
    variables[5] = 5.0


def compute_computed_constants(computed_constants):
    variables[3] = 3.0*variables[4]+variables[5]


def compute_variables(constants, computedConstants, algebraic):
    find_root_0(variables)
    variables[0] = variables[1]+variables[2]
