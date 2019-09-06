# The contents of this file was generated from version 0.2.0 of libCellML.
from math import *


__version__ = "0.2.0"

STATE_VECTOR_SIZE = 2
VARIABLE_VECTOR_SIZE = 1
VOI = {"component": "my_component", "name": "t", "units": "second"}

STATE_VECTOR_INFORMATION_ARRAY = [
    {"component": "my_component", "name": "x", "units": "dimensionless"},
    {"component": "my_component", "name": "y", "units": "dimensionless"},
]

VARIABLE_VECTOR_INFORMATION_ARRAY = [
    {"component": "my_component", "name": "epsilon", "units": "dimensionless"},
]


def create_state_vector():
    return [nan]*2


def create_rate_vector():
    return [nan]*2


def create_variable_vector():
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
