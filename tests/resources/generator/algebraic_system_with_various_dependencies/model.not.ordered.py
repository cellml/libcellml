# The content of this file was generated using the Python profile of libCellML 0.6.3.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.6.3"

VARIABLE_COUNT = 6


class VariableType(Enum):
    CONSTANT = 0
    COMPUTED_CONSTANT = 1
    ALGEBRAIC = 2


VARIABLE_INFO = [
    {"name": "c", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.ALGEBRAIC},
    {"name": "b", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.ALGEBRAIC},
    {"name": "d", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.ALGEBRAIC},
    {"name": "a", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.COMPUTED_CONSTANT},
    {"name": "y", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.CONSTANT},
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.CONSTANT}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


from nlasolver import nla_solve


def objective_function_0(u, f, data):
    variables = data[0]

    variables[0] = u[0]
    variables[1] = u[1]

    f[0] = 3.0*variables[3]+2.0*variables[1]+variables[0]-57.0
    f[1] = variables[3]+3.0*variables[1]-variables[0]-19.0


def find_root_0(variables):
    u = [nan]*2

    u[0] = variables[0]
    u[1] = variables[1]

    u = nla_solve(objective_function_0, u, 2, [variables])

    variables[0] = u[0]
    variables[1] = u[1]


def initialise_variables(variables):
    variables[0] = 1.0
    variables[1] = 1.0
    variables[4] = 5.0
    variables[5] = 3.0


def compute_computed_constants(variables):
    variables[3] = 3.0*variables[5]+variables[4]


def compute_variables(variables):
    find_root_0(variables)
    variables[2] = variables[1]+variables[0]
