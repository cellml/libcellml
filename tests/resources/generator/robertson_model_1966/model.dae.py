# The content of this file was generated using the Python profile of libCellML 0.6.0.

from enum import Enum
from math import *


__version__ = "0.5.0"
LIBCELLML_VERSION = "0.6.0"

STATE_COUNT = 2
CONSTANT_COUNT = 3
COMPUTED_CONSTANT_COUNT = 0
ALGEBRAIC_COUNT = 2

VOI_INFO = {"name": "t", "units": "dimensionless", "component": "main"}

STATE_INFO = [
    {"name": "y1", "units": "dimensionless", "component": "main"},
    {"name": "y2", "units": "dimensionless", "component": "main"}
]

CONSTANT_INFO = [
    {"name": "k1", "units": "dimensionless", "component": "main"},
    {"name": "k3", "units": "dimensionless", "component": "main"},
    {"name": "k2", "units": "dimensionless", "component": "main"}
]

COMPUTED_CONSTANT_INFO = [
]

ALGEBRAIC_INFO = [
    {"name": "y3", "units": "dimensionless", "component": "main"},
    {"name": "y2_scaled", "units": "dimensionless", "component": "main"}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_constants_array():
    return [nan]*CONSTANT_COUNT


def create_computed_constants_array():
    return [nan]*COMPUTED_CONSTANT_COUNT


def create_algebraic_array():
    return [nan]*ALGEBRAIC_COUNT


from nlasolver import nla_solve


def objective_function_0(u, f, data):
    voi = data[0]
    states = data[1]
    rates = data[2]
    constants = data[3]
    computed_constants = data[4]
    algebraic = data[5]

    algebraic[0] = u[0]

    f[0] = 1.0-(states[0]+states[1]+algebraic[0])


def find_root_0(voi, states, rates, constants, computed_constants, algebraic):
    u = [nan]*1

    u[0] = algebraic[0]

    u = nla_solve(objective_function_0, u, 1, [voi, states, rates, constants, computed_constants, algebraic])

    algebraic[0] = u[0]


def initialise_variables(states, rates, constants, computed_constants, algebraic):
    states[0] = 1.0
    states[1] = 0.0
    constants[0] = 0.04
    constants[1] = 1.0e4
    constants[2] = 3.0e7
    algebraic[0] = 0.0


def compute_computed_constants(constants, computed_constants):
    pass


def compute_rates(voi, states, rates, constants, computed_constants, algebraic):
    find_root_0(voi, states, rates, constants, computed_constants, algebraic)
    rates[0] = -constants[0]*states[0]+constants[1]*states[1]*algebraic[0]
    rates[1] = constants[0]*states[0]-constants[2]*pow(states[1], 2.0)-constants[1]*states[1]*algebraic[0]


def compute_variables(voi, states, rates, constants, computed_constants, algebraic):
    find_root_0(voi, states, rates, constants, computed_constants, algebraic)
    algebraic[1] = 10000.0*states[1]
