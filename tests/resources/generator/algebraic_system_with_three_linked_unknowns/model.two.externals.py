# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.5.0"

CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 3


class VariableType(Enum):
    CONSTANT = 0
    COMPUTED_CONSTANT = 1
    ALGEBRAIC = 2
    EXTERNAL = 3


VARIABLE_INFO = [
    {"name": "x", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.EXTERNAL},
    {"name": "y", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.ALGEBRAIC},
    {"name": "z", "units": "dimensionless", "component": "my_algebraic_system", "type": VariableType.EXTERNAL}
]


def create_variables_array():
    return [nan]*VARIABLE_COUNT


from nlasolver import nla_solve


def objective_function_0(u, f, data):
    variables = data[0]

    variables[1] = u[0]

    f[0] = 2.0*variables[0]+variables[1]-2.0*variables[2]-(-1.0)


def find_root_0(variables):
    u = [nan]*1

    u[0] = variables[1]

    u = nla_solve(objective_function_0, u, 1, [variables])

    variables[1] = u[0]


def objective_function_1(u, f, data):
    variables = data[0]

    variables[1] = u[0]

    f[0] = 3.0*variables[0]-3.0*variables[1]-variables[2]-5.0


def find_root_1(variables):
    u = [nan]*1

    u[0] = variables[1]

    u = nla_solve(objective_function_1, u, 1, [variables])

    variables[1] = u[0]


def objective_function_2(u, f, data):
    variables = data[0]

    variables[1] = u[0]

    f[0] = variables[0]-2.0*variables[1]+3.0*variables[2]-6.0


def find_root_2(variables):
    u = [nan]*1

    u[0] = variables[1]

    u = nla_solve(objective_function_2, u, 1, [variables])

    variables[1] = u[0]


def initialise_variables(variables, external_variable):
    variables[1] = 1.0
    variables[0] = external_variable(variables, 0)
    variables[2] = external_variable(variables, 2)


def compute_computed_constants(computed_constants):
    pass


def compute_variables(variables, external_variable):
    variables[0] = external_variable(variables, 0)
    variables[2] = external_variable(variables, 2)
    find_root_0(variables)
    find_root_1(variables)
    find_root_2(variables)
