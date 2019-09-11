# The contents of this file were generated from version 0.2.0 of libCellML.

from math import *


__version__ = "0.2.0"

STATE_COUNT = 0
VARIABLE_COUNT = 1

VOI_INFO = {"component": "", "name": "", "units": ""}

STATE_INFO = [
]

VARIABLE_INFO = [
    {"component": "my_component", "name": "x", "units": "dimensionless"}
]


def create_states_array():
    return [nan]*0


def create_variables_array():
    return [nan]*1


def initialize_constants(states, variables):
    variables[0] = 1.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    pass


def compute_variables(voi, states, rates, variables):
    pass
