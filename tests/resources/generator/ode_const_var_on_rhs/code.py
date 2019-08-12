from math import *


STATE_VECTOR_SIZE = 1
VARIABLE_VECTOR_SIZE = 1
VOI = {"name": "t", "units": "second"}

STATE_VECTOR_INFORMATION_ARRAY = [
    {"name": "x", "units": "dimensionless"},
]

VARIABLE_VECTOR_INFORMATION_ARRAY = [
    {"name": "a", "units": "per_s"},
]


def create_state_vector():
    return [nan]*1


def create_rate_vector():
    return [nan]*1


def create_variable_vector():
    return [nan]*1


def initialize_constants(states, variables):
    states[0] = 1.0
    variables[0] = 1.0


def compute_computed_constants(variables):
    pass


def compute_rates(voi, states, rates, variables):
    rates[0] = variables[0]


def compute_variables(voi, states, rates, variables):
    pass
