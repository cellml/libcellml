from math import *


__version__ = "0.2.0"

STATE_COUNT = 1
VARIABLE_COUNT = 2


STATE_VECTOR_INFORMATION_ARRAY = [
    ,
]

VARIABLE_VECTOR_INFORMATION_ARRAY = [
    ,
    ,
]


def create_states_array():
    pass


def create_variables_array():
    pass


def initialize_constants(states, variables):
    states[0] = 1.0
    variables[0] = 1.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = variables[0]


def compute_variables(voi, states, rates, variables):
    variables[1] = rates[0]
