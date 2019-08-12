from math import *


STATE_VECTOR_SIZE = 2
VARIABLE_VECTOR_SIZE = 2
VOI = {"name": "t", "units": "ms"}

STATE_VECTOR_INFORMATION_ARRAY = [
    {"name": "x", "units": "mM"},
    {"name": "y", "units": "mM"},
]

VARIABLE_VECTOR_INFORMATION_ARRAY = [
    {"name": "local_complex_maths", "units": "mM"},
    {"name": "two_x", "units": "milli_mole"},
]


def create_state_vector():
    return [nan]*2


def create_rate_vector():
    return [nan]*2


def create_variable_vector():
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
