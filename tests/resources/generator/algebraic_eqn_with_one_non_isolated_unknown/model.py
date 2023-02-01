# The content of this file was generated using the Python profile of libCellML 0.4.0.

from enum import Enum
from math import *


__version__ = "0.3.2"
LIBCELLML_VERSION = "0.4.0"

VARIABLE_COUNT = 4


class VariableType(Enum):
    CONSTANT = 0
    COMPUTED_CONSTANT = 1
    ALGEBRAIC = 2


VARIABLE_INFO = [
    {"name": "b", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.CONSTANT},
    {"name": "c", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.CONSTANT},
    {"name": "d", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.CONSTANT},
    {"name": "a", "units": "dimensionless", "component": "my_algebraic_eqn", "type": VariableType.ALGEBRAIC}
]


def create_variables_array():
    return [nan] * VARIABLE_COUNT


def objective_function_0(u, f, data):
    variables = data[0]

    variables[3] = u[0]

    f[0] = variables[0] + variables[1] - (variables[3] + variables[2])


def find_root_0(variables):
    u = [nan]*1

    u[0] = variables[3]

    nla_solve(objective_function_0, u, 1, (variables))

    variables[3] = u[0]


def initialise_variables(variables):
    variables[0] = 3.0
    variables[1] = 5.0
    variables[2] = 7.0
    variables[3] = 1.0


def compute_computed_constants(variables):
    find_root_0(variables)


def compute_variables(variables):
    pass
