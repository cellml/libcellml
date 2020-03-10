# The content of this file was generated using the Python profile of libCellML 0.2.0.

from enum import Enum
from math import *


__version__ = "0.1.0"
LIBCELLML_VERSION = "0.2.0"

STATE_COUNT = 7
VARIABLE_COUNT = 3


class VariableType(Enum):
    CONSTANT = 1
    COMPUTED_CONSTANT = 2
    ALGEBRAIC = 3


VOI_INFO = {"name": "t", "units": "ms", "component": "environment"}

STATE_INFO = [
    {"name": "y", "units": "mV", "component": "states"},
    {"name": "x", "units": "mV", "component": "t"},
    {"name": "scaled_x", "units": "volt", "component": "t"},
    {"name": "z", "units": "mV", "component": "t"},
    {"name": "x", "units": "mV", "component": "scaled_t"},
    {"name": "scaled_x", "units": "volt", "component": "scaled_t"},
    {"name": "scaled_z", "units": "volt", "component": "scaled_t"}
]

VARIABLE_INFO = [
    {"name": "k", "units": "mV", "component": "constants", "type": VariableType.CONSTANT},
    {"name": "voi", "units": "ms", "component": "t", "type": VariableType.ALGEBRAIC},
    {"name": "scaled_voi", "units": "second", "component": "scaled_t", "type": VariableType.ALGEBRAIC}
]


def create_states_array():
    return [nan]*STATE_COUNT


def create_variables_array():
    return [nan]*VARIABLE_COUNT


def initialize_states_and_constants(states, variables):
    states[0] = 789.0
    states[1] = 1.0
    states[2] = 3.0
    states[3] = 1.23
    states[4] = 101.0
    states[5] = 103.0
    states[6] = 0.001*7.89
    variables[0] = 123.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = 1.23
    rates[1] = variables[0]+states[0]+states[3]
    rates[2] = 0.001*variables[0]+0.001*states[0]
    rates[3] = variables[0]+states[0]
    rates[4] = 1000.0*(variables[0]+states[0])
    rates[5] = 1000.0*(0.001*variables[0]+0.001*states[0]+states[6])
    rates[6] = 1000.0*(0.001*variables[0]+0.001*states[0])


def compute_variables(voi, states, rates, variables):
    variables[1] = voi
    variables[2] = 0.001*voi
