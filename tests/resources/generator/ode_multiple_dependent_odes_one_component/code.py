# The content of this file was generated using the Python profile of libCellML 0.2.0.

from math import *


LIBCELLML_VERSION = "0.2.0"

STATE_COUNT = 2
VARIABLE_COUNT = 1

VOI_INFO = {"component": "my_component", "name": "t", "units": "second"}

STATE_INFO = [
    {"component": "my_component", "name": "x", "units": "dimensionless"},
    {"component": "my_component", "name": "y", "units": "dimensionless"}
]

VARIABLE_INFO = [
    {"component": "my_component", "name": "epsilon", "units": "dimensionless"}
]


def create_states_array():
    return [nan]*2


def create_variables_array():
    return [nan]*1


def initialize_constants(states, variables):
    states[0] = -2.0
    states[1] = 0.0
    variables[0] = 1.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = states[1]*1.0
    rates[1] = (variables[0]*(1.0-pow(states[0], 2.0))*states[1]-states[0])*1.0


def compute_variables(voi, states, rates, variables):
    pass
