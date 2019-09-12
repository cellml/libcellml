# The content of this file was generated using the Python profile of libCellML 0.2.0.

from math import *


LIBCELLML_VERSION = "0.2.0"

STATE_COUNT = 2
VARIABLE_COUNT = 2

VOI_INFO = {"name": "t", "units": "ms", "component": "circle_x"}

STATE_INFO = [
    {"name": "x", "units": "mM", "component": "circle_x_source"},
    {"name": "y", "units": "mM", "component": "circle_y_implementation"}
]

VARIABLE_INFO = [
    {"name": "local_complex_maths", "units": "mM", "component": "circle_sibling"},
    {"name": "two_x", "units": "milli_mole", "component": "circle_x_sibling"}
]


def create_states_array():
    return [nan]*2


def create_variables_array():
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
