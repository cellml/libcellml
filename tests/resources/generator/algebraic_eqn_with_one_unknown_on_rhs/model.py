# The content of this file was generated using the Python profile of libCellML 0.2.0.

from enum import Enum
from math import *

__version__ = "0.3.0"
LIBCELLML_VERSION = "0.2.0"

VARIABLE_COUNT = 4


class VariableType(Enum):
    CONSTANT = 1
    COMPUTED_CONSTANT = 2
    ALGEBRAIC = 3


VARIABLE_INFO = [
    {"name": "b", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.CONSTANT},
    {"name": "c", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.CONSTANT},
    {"name": "d", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.CONSTANT},
    {"name": "a", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.ALGEBRAIC}
]


def create_variables_array():
    return [nan] * VARIABLE_COUNT


def obj_func_0(u, f, data):
    variables = data[0]

    variables[3] = u[0]

    f[0] = variables[0] + variables[1] - (variables[3] + variables[2]);


def root_find_0(variables):
    u = [1.0]

    nla_solve(obj_func_0, u, 1, (variables))

    variables[3] = u[0]


def initialise_constants(variables):
    variables[0] = 3.0
    variables[1] = 5.0
    variables[2] = 7.0


def compute_computed_constants(variables):
    root_find_0(variables)


def compute_variables(variables):
    pass
