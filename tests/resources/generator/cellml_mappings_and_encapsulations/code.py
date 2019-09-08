# The contents of this file was generated from version 0.2.0 of libCellML.
from math import *


__version__ = "0.2.0"

STATE_VECTOR_SIZE = 2
VARIABLE_VECTOR_SIZE = 2

VOI_INFORMATION = {"component": "circle_x", "name": "t", "units": "ms"}

STATE_VECTOR_INFORMATION_ARRAY = [
    {"component": "circle_x_source", "name": "x", "units": "mM"},
    {"component": "circle_y_implementation", "name": "y", "units": "mM"},
]

VARIABLE_VECTOR_INFORMATION_ARRAY = [
    {"component": "circle_sibling", "name": "local_complex_maths", "units": "mM"},
    {"component": "circle_x_sibling", "name": "two_x", "units": "milli_mole"},
]


def create_states():
    return [nan]*2


def create_variables():
    return [nan]*2


def initialize_constants(states, variables):
    states[0] = 0.0
    states[1] = 1.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = -states[1]*1.0
    rates[1] = states[0]*1.0


def compute_variables(voi, states, rates, variables):
    variables[0] = states[1]+5.0*states[1]/3.0+1.0*exp(states[1]/2.0)
    variables[1] = 2.0*states[0]
