# The content of this file was generated using the Python profile of libCellML 0.4.0.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.4.0"

STATE_COUNT = 2
VARIABLE_COUNT = 5


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "t", "units": "dimensionless", "component": "main", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "y1", "units": "dimensionless", "component": "main", "type": VariableType.STATE},
    {"name": "y2", "units": "dimensionless", "component": "main", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "k1", "units": "dimensionless", "component": "main", "type": VariableType.CONSTANT},
    {"name": "k3", "units": "dimensionless", "component": "main", "type": VariableType.CONSTANT},
    {"name": "y3", "units": "dimensionless", "component": "main", "type": VariableType.ALGEBRAIC},
    {"name": "k2", "units": "dimensionless", "component": "main", "type": VariableType.CONSTANT},
    {"name": "y2_scaled", "units": "dimensionless", "component": "main", "type": VariableType.ALGEBRAIC}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


from nlasolver import nla_solve


def objective_function_0(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[2] = u[0]

    f[0] = 1.0-(states[0]+states[1]+variables[2])


def find_root_0(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[2]

    nla_solve(objective_function_0, u, 1, (voi, states, rates, variables))

    variables[2] = u[0]


def initialise_variables(states, variables):
    variables[0] = 0.04
    variables[1] = 1.0e4
    variables[2] = 0.0
    variables[3] = 3.0e7
    states[0] = 1.0
    states[1] = 0.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    find_root_0(voi, states, rates, variables)
    rates[0] = -variables[0]*states[0]+variables[1]*states[1]*variables[2]
    rates[1] = variables[0]*states[0]-variables[3]*pow(states[1], 2.0)-variables[1]*states[1]*variables[2]


def compute_variables(voi, states, rates, variables):
    find_root_0(voi, states, rates, variables)
    variables[4] = 10000.0*states[1]
