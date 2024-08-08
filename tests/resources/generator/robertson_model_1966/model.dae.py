# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 2
CONSTANT_COUNT = 3
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 2


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
    {"name": "k2", "units": "dimensionless", "component": "main", "type": VariableType.CONSTANT},
    {"name": "y3", "units": "dimensionless", "component": "main", "type": VariableType.ALGEBRAIC},
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

    algebraic[0] = u[0]

    f[0] = 1.0-(states[0]+states[1]+algebraic[0])


def find_root_0(voi, states, rates, variables):
    u = [nan]*1

    u[0] = algebraic[0]

    u = nla_solve(objective_function_0, u, 1, [voi, states, rates, variables])

    algebraic[0] = u[0]


def initialise_variables(states, rates, constants):
    constants[0] = 0.04
    constants[1] = 1.0e4
    constants[2] = 3.0e7
    algebraic[0] = 0.0
    states[0] = 1.0
    states[1] = 0.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    find_root_0(voi, states, rates, variables)
    rates[0] = -constants[0]*states[0]+constants[1]*states[1]*algebraic[0]
    rates[1] = constants[0]*states[0]-constants[2]*pow(states[1], 2.0)-constants[1]*states[1]*algebraic[0]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    find_root_0(voi, states, rates, variables)
    algebraic[1] = 10000.0*states[1]
