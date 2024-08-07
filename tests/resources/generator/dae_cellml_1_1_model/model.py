# The content of this file was generated using the Python profile of libCellML 0.5.0.

from enum import Enum
from math import *


__version__ = "0.4.0"
LIBCELLML_VERSION = "0.5.0"

STATE_COUNT = 2
CONSTANT_COUNT = 0
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 10


class VariableType(Enum):
    VARIABLE_OF_INTEGRATION = 0
    STATE = 1
    CONSTANT = 2
    COMPUTED_CONSTANT = 3
    ALGEBRAIC = 4


VOI_INFO = {"name": "t", "units": "second", "component": "main", "type": VariableType.VARIABLE_OF_INTEGRATION}

STATE_INFO = [
    {"name": "q_1", "units": "coulomb", "component": "main", "type": VariableType.STATE},
    {"name": "v_3", "units": "C_per_s", "component": "main", "type": VariableType.STATE}
]

VARIABLE_INFO = [
    {"name": "v_1", "units": "C_per_s", "component": "main", "type": VariableType.ALGEBRAIC},
    {"name": "v_in", "units": "C_per_s", "component": "main", "type": VariableType.CONSTANT},
    {"name": "v_2", "units": "C_per_s", "component": "main", "type": VariableType.ALGEBRAIC},
    {"name": "v_out", "units": "C_per_s", "component": "main", "type": VariableType.CONSTANT},
    {"name": "u_1", "units": "J_per_C", "component": "main", "type": VariableType.ALGEBRAIC},
    {"name": "u_2", "units": "J_per_C", "component": "main", "type": VariableType.ALGEBRAIC},
    {"name": "u_3", "units": "J_per_C", "component": "main", "type": VariableType.ALGEBRAIC},
    {"name": "C", "units": "C2_per_J", "component": "main", "type": VariableType.CONSTANT},
    {"name": "R", "units": "Js_per_C2", "component": "main", "type": VariableType.CONSTANT},
    {"name": "L", "units": "Js2_per_C2", "component": "main", "type": VariableType.CONSTANT}
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

    variables[0] = u[0]

    f[0] = variables[1]-(variables[0]+variables[2])


def find_root_0(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[0]

    u = nla_solve(objective_function_0, u, 1, [voi, states, rates, variables])

    variables[0] = u[0]


def objective_function_1(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    variables = data[3]

    variables[6] = u[0]

    f[0] = variables[4]-(variables[5]+variables[6])


def find_root_1(voi, states, rates, variables):
    u = [nan]*1

    u[0] = variables[6]

    u = nla_solve(objective_function_1, u, 1, [voi, states, rates, variables])

    variables[6] = u[0]


def initialise_variables(states, rates, constants):
    variables[0] = 0.0
    variables[1] = 1.0
    variables[3] = 1.0
    variables[6] = 0.0
    variables[7] = 20.0
    variables[8] = 2.0
    variables[9] = 10.0
    states[0] = 1.0
    states[1] = 0.0


def compute_computed_constants(computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computedConstants, algebraic):
    variables[2] = states[1]+variables[3]
    find_root_0(voi, states, rates, variables)
    rates[0] = variables[0]
    variables[4] = states[0]/variables[7]
    variables[5] = variables[8]*variables[2]
    find_root_1(voi, states, rates, variables)
    rates[1] = variables[6]/variables[9]


def compute_variables(voi, states, rates, variables):
    variables[2] = states[1]+variables[3]
    find_root_0(voi, states, rates, variables)
    variables[4] = states[0]/variables[7]
    variables[5] = variables[8]*variables[2]
    find_root_1(voi, states, rates, variables)
